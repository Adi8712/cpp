#include "core.hpp"

#include <atomic>
#include <bits/sockaddr.h>
#include <cerrno>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

namespace core {
    std::atomic<bool> run(true);
    
    MySocket::MySocket(int family, sa_family_t type) {
        if (type != SOCK_DGRAM) {
            LOGGER(ERR_NOT_UDP);
        }

        sfd = socket(family, type, PROTOCOL);
        if (sfd == -1) {
            LOGGER(ERR_SOCKET);
        }

        addr.sin_family = DOMAIN;
        addr.sin_port = PORT;
        addr.sin_addr.s_addr = ADDRESS;        
    }

    void MySocket::listener() {
        if (bind(sfd, (struct sockaddr*) &addr, sizeof(addr)) == -1) {
            LOGGER(ERR_BIND);
        }
        
        while (run.load()) {
            char buf[1024];
            if(read(sfd, buf, 1024) == -1) {
                LOGGER(ERR_READING);
            }
    
            printf("READING: \t%s\n", buf);
        }
    }

    void MySocket::sender(std::string msg) {        
        if (sendto(sfd, msg.data(), sizeof(msg), 0, (struct sockaddr*) &addr, sizeof(addr)) == -1) {
            LOGGER(ERR_WRITING);
        }
    }
    
    MySocket::~MySocket() {
        close(sfd);
    }
}
