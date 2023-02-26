
#include "../../include/Reactor/inet_address.h"

#include <string.h>

namespace search_engine {

InetAddress::InetAddress(const string& ip, unsigned short port) {
    memset(&_servAddr, 0, sizeof(struct sockaddr_in));
    _servAddr.sin_family = AF_INET;
    _servAddr.sin_addr.s_addr = inet_addr(ip.c_str()); // host->network
    _servAddr.sin_port = htons(port);
}

InetAddress::InetAddress(const struct sockaddr_in& servAddr)
    : _servAddr(servAddr) { }

} // namespace search_engine
