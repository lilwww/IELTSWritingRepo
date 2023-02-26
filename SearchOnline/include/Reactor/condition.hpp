
#ifndef __SE_CONDITION__
#define __SE_CONDITION__

#include <stdio.h>
#include <pthread.h>

#include "mutex_lock.h"
#include "../disallow_copy_assign.h"

namespace search_engine {

class MutexLock; 

class Condition {
public:
    Condition(MutexLock &mutex)
    : _mutex(mutex) {
        int ret = pthread_cond_init(&_cond, nullptr);
        if (ret) {
            perror("pthread_cond_init");
        }
    }

    ~Condition() {
        int ret = pthread_cond_destroy(&_cond);
        if (ret) {
            perror("pthread_cond_destroy");
        }
    }

    void wait() {
        int ret = pthread_cond_wait(&_cond, _mutex.get_mutex_lock_ptr());
        if (ret) {
            perror("pthread_cond_wait");
        }
    }

    void notify() {
        int ret = pthread_cond_signal(&_cond);
        if (ret) {
            perror("pthread_cond_signal");
        }
    }

    void notifyAll() {
        int ret = pthread_cond_broadcast(&_cond);
        if (ret) {
            perror("pthread_cond_broadcast");
        }
    }

private:
    DISALLOW_COPY_AND_ASSIGN(Condition);

    pthread_cond_t   _cond;
    MutexLock&       _mutex;
};

} // namespace search_engine

#endif // __SE_CONDITION__
