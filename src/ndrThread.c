#include "ndrThread.h"
#include <stdlib.h>

typedef enum ndrTaskState {
    NDR_TASK_STATE_EMPTY,
    NDR_TASK_STATE_PENDING,
    NDR_TASK_STATE_BUSY
} ndrTaskState;

typedef struct ndrTask {
    ndrTaskState state;
    ndrThreadRoutine routine;
    void* args;
} ndrTask;

typedef struct ndrThreadPool_t {
    bool active;
    uint32_t maxThreads;
    uint32_t threadCount;
    uint32_t maxTasks;
    uint32_t workCount;
    ndrTask* tasks;
    ndrMutex mutex;
    ndrCond startWork;
    ndrCond endWork;
} ndrThreadPool_t, *ndrThreadPool;

void workerRoutine(void* args);
uint32_t getWorkerIndex(ndrThreadPool threadPool, ndrTaskState state);

bool ndrCreateThreadPool(uint32_t maxThreads, uint32_t maxTasks, ndrThreadPool* result)
{
    if(maxThreads < 2 || maxTasks < maxThreads || result == NULL)
        return false;

    // allocate enough space for the thread pool and the workers
    size_t workSize = sizeof(ndrTask) * maxTasks;
    *result = malloc(sizeof(ndrThreadPool_t) + workSize);

    // initialize thread pool
    (*result)->active = true;
    (*result)->maxThreads = maxThreads;
    (*result)->threadCount = maxThreads;
    (*result)->maxTasks = maxTasks;
    (*result)->workCount = 0;
    (*result)->tasks = NDR_PTR_OFFSET((*result), sizeof(ndrThreadPool_t));
    ndrCreateMutex(&(*result)->mutex);
    ndrCreateCond(&(*result)->startWork);
    ndrCreateCond(&(*result)->endWork);

    // initialize tasks
    for(uint32_t i = 0; i < maxTasks; i++)
        (*result)->tasks[i].state = NDR_TASK_STATE_EMPTY;

    // initialize worker threads
    for(uint32_t i = 0; i < maxThreads; i++)
        ndrCreateThread(workerRoutine, *result, NULL);
    
    return true;
}
void ndrDestroyThreadPool(ndrThreadPool threadPool)
{
    if(threadPool == NULL)
        return;

    ndrLockMutex(threadPool->mutex);
    threadPool->active = false;
    ndrSignalAllCond(threadPool->startWork);
    ndrUnlockMutex(threadPool->mutex);
    ndrWaitThreadPool(threadPool);

    ndrDestroyMutex(threadPool->mutex);
    ndrDestroyCond(threadPool->startWork);
    ndrDestroyCond(threadPool->endWork);
    free(threadPool);
}

void ndrWaitThreadPool(ndrThreadPool threadPool)
{
    ndrLockMutex(threadPool->mutex);
    while(threadPool->active && threadPool->workCount > 0 || !threadPool->active && threadPool->threadCount > 0)
        ndrWaitCond(threadPool->endWork, threadPool->mutex, NDR_TIME_INFINITE);
    ndrUnlockMutex(threadPool->mutex);
}

void ndrAddTask(ndrThreadPool threadPool, ndrThreadRoutine routine, void* args)
{
    ndrLockMutex(threadPool->mutex);
    while(threadPool->workCount >= threadPool->maxThreads)
        ndrWaitCond(threadPool->endWork, threadPool->mutex, NDR_TIME_INFINITE);

    uint32_t index;
    while(true)
    {
        index = getWorkerIndex(threadPool, NDR_TASK_STATE_EMPTY);
        if(index != -1)
            break;
    }

    threadPool->tasks[index].state = NDR_TASK_STATE_PENDING;
    threadPool->tasks[index].routine = routine;
    threadPool->tasks[index].args = args;
    threadPool->workCount++;
    ndrSignalCond(threadPool->startWork);
    ndrUnlockMutex(threadPool->mutex);
}

void workerRoutine(void* args)
{
    ndrThreadPool threadPool = args;
    while(true)
    {
        ndrLockMutex(threadPool->mutex);
        while(threadPool->active && threadPool->workCount == 0)
            ndrWaitCond(threadPool->startWork, threadPool->mutex, NDR_TIME_INFINITE); 

        if(!threadPool->active)
            break;

        uint32_t index = getWorkerIndex(threadPool, NDR_TASK_STATE_PENDING);
        if(index == -1)
        {
            ndrUnlockMutex(threadPool->mutex);
            continue;
        }

        threadPool->tasks[index].state = NDR_TASK_STATE_BUSY;
        ndrThreadRoutine routine = threadPool->tasks[index].routine;
        void* args = threadPool->tasks[index].args;
        ndrUnlockMutex(threadPool->mutex);

        routine(args);

        ndrLockMutex(threadPool->mutex);
        threadPool->tasks[index].state = NDR_TASK_STATE_EMPTY;
        threadPool->tasks[index].routine = NULL;
        threadPool->tasks[index].args = NULL;
        threadPool->workCount--;
        ndrSignalCond(threadPool->endWork);
        ndrUnlockMutex(threadPool->mutex);
    } 
    threadPool->threadCount--;
    ndrSignalCond(threadPool->endWork);
    ndrUnlockMutex(threadPool->mutex);
}

uint32_t getWorkerIndex(ndrThreadPool threadPool, ndrTaskState state)
{
    for(uint32_t i = 0; i < threadPool->maxTasks; i++)
    {
        if(threadPool->tasks[i].state == state)
            return i;
    }
    return -1;
}