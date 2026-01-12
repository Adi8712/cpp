#include "core.hpp"

#include <atomic>
#include <bits/sockaddr.h>
#include <cerrno>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

namespace core {
    std::atomic<bool> run(true);
    
    MySocket::MySocket(int family, sa_family_t type, in_port_t port, in_addr_t address) {
        if (type != SOCK_DGRAM) {
            LOGGER(ERR_NOT_UDP);
        }

        sfd = socket(family, type, PROTOCOL);
        if (sfd == -1) {
            LOGGER(ERR_SOCKET);
        }

        addr.sin_family = DOMAIN;
        addr.sin_port = port;
        addr.sin_addr.s_addr = address;
    }

    void MySocket::listener() {
        if (bind(sfd, (struct sockaddr*) &addr, sizeof(addr)) == -1) {
            LOGGER(ERR_BIND);
        }
        while (run.load()) {
            char buf[32];
            if(read(sfd, buf, 32) == -1) {
                LOGGER(ERR_READING);
            }

            long now = std::chrono::steady_clock::now().time_since_epoch().count();
            std::printf("Received: %s\nAt: %ld\n", buf, now);
        }
    }

    void MySocket::sender(std::string msg) {
        long now = std::chrono::steady_clock::now().time_since_epoch().count();
        std::printf("Sending: %s\nAt: %ld\n", msg.data(), now);
        if (sendto(sfd, msg.data(), msg.size(), 0, (struct sockaddr*) &addr, sizeof(addr)) == -1) {
            LOGGER(ERR_WRITING);
        }
    }
    
    MySocket::~MySocket() {
        close(sfd);
    }
}
