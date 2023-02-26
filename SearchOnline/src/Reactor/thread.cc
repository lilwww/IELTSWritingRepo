
#include "../../include/Reactor/thread.h"

namespace search_engine {

__thread const char* name = "current_thread";

Thread::Thread(ThreadCallback&& cb, const string&name)
    : _thid(0),
      _name(name), 
      _isRunning(false),
      _cbPool(std::move(cb)) { }

void *Thread::threadFunc(void *arg) {
    Thread* pthread = static_cast<Thread*>(arg);
    name = pthread->_name.c_str();

    if (pthread) {
        pthread->_cbPool();
    }

    pthread_exit(nullptr);
}

} // namespace search_engine
