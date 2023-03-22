#include "ndrThread.h"
#include <stdlib.h>
#if defined(_WIN32)
#define WIN32_LEAN
#include <Windows.h>

typedef struct ndrMutex_t {
    CRITICAL_SECTION handle;
    bool locked;
} ndrMutex_t, *ndrMutex;

typedef struct ndrCond_t {
    CONDITION_VARIABLE handle;
} ndrCond_t, *ndrCond;

typedef struct ndrThreadInfo {
    ndrThreadRoutine routine;
    void* args;
} ndrThreadInfo;

DWORD WINAPI ThreadProc(LPVOID lpParam);

// mutex
bool ndrCreateMutex(ndrMutex* result)
{
    if(result == NULL)
        return false;

    *result = malloc(sizeof(ndrMutex_t));
    InitializeCriticalSection(&(*result)->handle);
    (*result)->locked = false;
    return true;
}

void ndrDestroyMutex(ndrMutex mutex)
{
    if(mutex == NULL || !mutex->locked)
        return;

    DeleteCriticalSection(&mutex->handle);
    free(mutex);
}

void ndrLockMutex(ndrMutex mutex)
{
    if(mutex == NULL)
        return;

    EnterCriticalSection(&mutex->handle);
    mutex->locked = true;
}

void ndrUnlockMutex(ndrMutex mutex)
{
    if(mutex == NULL)
        return;

    LeaveCriticalSection(&mutex->handle);
    mutex->locked = false;
}

// cond
bool ndrCreateCond(ndrCond* result)
{
    if(result == NULL)
        return false;

    *result = malloc(sizeof(ndrCond_t));
    InitializeConditionVariable(&(*result)->handle);
    return true;
}

void ndrDestroyCond(ndrCond cond)
{
    if(cond == NULL)
        return;

    free(cond);
}

void ndrWaitCond(ndrCond cond, ndrMutex mutex, ndrTime ms)
{
    if(cond == NULL)
        return;

    SleepConditionVariableCS(&cond->handle, &mutex->handle, (DWORD)ms);
}

void ndrSignalCond(ndrCond cond)
{
    if(cond == NULL)
        return;

    WakeConditionVariable(&cond->handle);
}

void ndrSignalAllCond(ndrCond cond)
{
    if(cond == NULL)
        return;

    WakeAllConditionVariable(&cond->handle);
}

// thread
bool ndrCreateThread(ndrThreadRoutine routine, void* args, ndrThread* result)
{
    if(routine == NULL)
        return false;

    ndrThreadInfo* info = malloc(sizeof(ndrThreadInfo));
    info->routine = routine;
    info->args = args;
    ndrThread thread;
    thread = CreateThread(NULL, 0, ThreadProc, info, 0, NULL);
    if(result != NULL)
        *result = thread;
    return true;
}

void ndrDestroyThread(ndrThread thread)
{
    WaitForSingleObject(thread, INFINITE);
}

uint32_t ndrThreadID() { return (uint32_t)GetCurrentThreadId(); }

void ndrWaitThread(ndrTime ms)
{
    Sleep((DWORD)ms);
}

DWORD WINAPI ThreadProc(LPVOID lpParam)
{
    ndrThreadInfo* info = lpParam;
    ndrThreadRoutine routine = info->routine;
    void* args = info->args;
    free(info);
    routine(args);
    return EXIT_SUCCESS;
}
#endif