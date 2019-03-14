#include "mutex.h"

Mutex::Mutex() {
#ifdef __WIN32__
    InitializeCriticalSection(&cs);
#else
    pthread_mutexattr_t mAttr;
    pthread_mutexattr_settype(&mAttr, PTHREAD_MUTEX_RECURSIVE_NP);
    pthread_mutex_init(&cs, &mAttr);
    pthread_mutexattr_destroy(&mAttr);
#endif
}

void Mutex::lock() {
#ifdef __WIN32__
    EnterCriticalSection(&cs);
#else
    pthread_mutex_lock (&cs);
#endif
}

void Mutex::unlock() {
#ifdef __WIN32__
    LeaveCriticalSection(&cs);
#else
    pthread_mutex_unlock (&cs);
#endif
}

Mutex::~Mutex() {
#ifdef __WIN32__
    DeleteCriticalSection(&cs);
#else
    pthread_mutex_destroy (&cs);
#endif
}
