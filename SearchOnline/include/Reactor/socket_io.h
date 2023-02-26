
#ifndef __SE_SOCKET_IO_H__
#define __SE_SOCKET_IO_H__

namespace search_engine {

class SocketIO {
public:
    explicit SocketIO(int fd) : _fd(fd) { }
    ~SocketIO() = default;

    int readN(char* buf, int len);
    int readLine(char* buf, int len);
    int writeN(const char* buf, int len);

private:
    int _fd;
};

} // namespace search_engine

#endif // __SE_SOCKET_IO_H__
