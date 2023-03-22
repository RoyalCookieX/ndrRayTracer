#pragma once
#include "defines.h"

// A routine that a thread executes.
typedef void(*ndrThreadRoutine)(void* args);

// Used for syncronization of shared resources across multiple threads.
typedef struct ndrMutex_t *ndrMutex;
// Used for syncronization of multiple threads.
typedef struct ndrCond_t *ndrCond;
// Used for executing tasks in parallel.
typedef void* ndrThread;
// Manages and syncronizes multiple threads.
typedef struct ndrThreadPool_t *ndrThreadPool;

// Creates a mutex.
bool ndrCreateMutex(ndrMutex* result);
// Destroys a mutex.
void ndrDestroyMutex(ndrMutex mutex);
// Locks a mutex.
void ndrLockMutex(ndrMutex mutex);
// Unlocks a mutex.
void ndrUnlockMutex(ndrMutex mutex);

// Creates a condition variable.
bool ndrCreateCond(ndrCond* result);
// Destroys a condition variable.
void ndrDestroyCond(ndrCond cond);
// Stops a thread until the condition variable is signaled, or until 'ms' milliseconds pass.
void ndrWaitCond(ndrCond cond, ndrMutex mutex, ndrTime ms);
// Signals a condition variable. A thread waiting on the condition variable will resume.
void ndrSignalCond(ndrCond cond);
// Signals all condition variables. Any threads waiting on the condition variable will resume.
void ndrSignalAllCond(ndrCond cond);

// Creates a thread.
bool ndrCreateThread(ndrThreadRoutine routine, void* args, ndrThread* result);
// Destroys a thread.
void ndrDestroyThread(ndrThread thread);
// Obtains the current thread's ID.
uint32_t ndrThreadID();
// Waits for 'ms' milliseconds to pass.
void ndrWaitThread(ndrTime ms);

// Creates a thread pool.
bool ndrCreateThreadPool(uint32_t maxThreads, uint32_t maxTasks, ndrThreadPool* result);
// Destroys a thread pool.
void ndrDestroyThreadPool(ndrThreadPool threadPool);
// Waits for the thread pool to finish all its tasks.
void ndrWaitThreadPool(ndrThreadPool threadPool);
// Runs a task on the thread pool.
void ndrAddTask(ndrThreadPool threadPool, ndrThreadRoutine routine, void* args);