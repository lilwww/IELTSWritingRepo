
#include "../../include/Reactor/mutex_lock.h"

#include <stdio.h>

namespace search_engine {

MutexLock::MutexLock() {
    int ret = pthread_mutex_init(&_mutex, nullptr);
    if (ret) {
        perror("pthread_mutex_init");
    }
}

MutexLock::~MutexLock() {
    int ret = pthread_mutex_destroy(&_mutex);
    if (ret) {
        perror("pthread_mutex_destroy");
    }
}

void MutexLock::lock() {
    int ret = pthread_mutex_lock(&_mutex);
    if (ret) {
        perror("pthread_mutex_lock");
    }
}

void MutexLock::unlock() {
    int ret = pthread_mutex_unlock(&_mutex);
    if(ret) {
        perror("pthread_mutex_unlock");
    }
}

} // namespace search_engine
