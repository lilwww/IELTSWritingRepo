
#ifndef __SE_EVENTLOOP_H__
#define __SE_EVENTLOOP_H__

#include <sys/epoll.h>

#include <vector>
#include <map>
#include <memory>
#include <functional>

#include "tcp_connection.h"
#include "mutex_lock.h"

using std::vector;
using std::map;
using std::shared_ptr;
using std::function;


namespace search_engine {

class Acceptor;

using TcpConnectionPtr      = shared_ptr<TcpConnection>;
using TcpConnectionCallback = function<void(const TcpConnectionPtr&)>;
using Functor               = function<void()>;

class EventLoop {
public:
    EventLoop(Acceptor& acceptor);
    ~EventLoop();

    void setConnectionCallback(TcpConnectionCallback&& cb) {
        _onConectionCb = std::move(cb);
    }
    void setMessageCallback(TcpConnectionCallback&& cb) {
        _onMessageCb = std::move(cb);
    }
    void setCloseCallback(TcpConnectionCallback&& cb) {
        _onCloseCb = std::move(cb);
    }

    void loop();
    void unloop();
    void runInLoop(Functor&& cb);

private:
    void waitEpollFd();
    void handleNewConnection();
    void handleMessage(int fd);

    void handleRead();
    void doPendingFunctors();

    int  createEpollFd();
    int  createEventFd();
    void addEpollReadFd(int fd);
    void delEpollReadFd(int fd);

    void wakeup();

private:
    int                          _epfd;
    int                          _evfd;
    Acceptor&                    _acceptor;
    bool                         _isLooping;
    vector<struct epoll_event>   _evtList;
    map<int, TcpConnectionPtr>   _conns;

    TcpConnectionCallback   _onConectionCb;
    TcpConnectionCallback   _onMessageCb;
    TcpConnectionCallback   _onCloseCb;

    vector<Functor>   _pendingsCb;
    MutexLock         _mutex;
};

} // namespace search_engine

#endif // __SE_EVENTLOOP_H__
