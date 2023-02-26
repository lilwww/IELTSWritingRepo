
#ifndef __SE_MUTEX_LOCK_H__
#define __SE_MUTEX_LOCK_H__

#include <pthread.h>

#include "../disallow_copy_assign.h"

namespace search_engine {

class MutexLock {
public:
    MutexLock();
    ~MutexLock();
    void lock();
    void unlock();
    pthread_mutex_t* get_mutex_lock_ptr()   { return & _mutex; }

private:
    DISALLOW_COPY_AND_ASSIGN(MutexLock);

    pthread_mutex_t _mutex;
};


class MutexLockGuard {
public:
    MutexLockGuard(MutexLock &mutex)
    : _mutex(mutex)   {
        _mutex.lock();
    }

    ~MutexLockGuard() { _mutex.unlock(); }

private:
    MutexLock& _mutex;
};

} // namespace search_engine

#endif // __SE_MUTEX_LOCK_H__
