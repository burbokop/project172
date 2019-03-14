#ifndef MUTEX_H
#define MUTEX_H

#ifdef __WIN32__
#include <windows.h>
typedef CRITICAL_SECTION CS;
#else
#include <pthread.h>
typedef pthread_mutex_t CS;
#endif

class Mutex {
private:
    CS cs;
public:
    Mutex();
    void lock();
    void unlock();
    ~Mutex();
};

#endif // MUTEX_H
