#pragma once

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

#define ERR_NOT_UDP -1
#define ERR_SOCKET -2
#define ERR_BIND -3
#define ERR_READING -4
#define ERR_WRITING -5

#define LOGGER(macro) do { \
    fprintf(stderr, "%s\t%s\t%s:%d\n", strerror(errno), #macro, __FILE__, __LINE__); \
    exit(macro); \
} while(0)

#define DOMAIN AF_INET
#define SOCKTYPE SOCK_DGRAM
#define PROTOCOL 0
#define LISTEN_BACKLOG 50

namespace core {
    extern std::atomic<bool> run;
    
    class MySocket {
        private:
            int sfd;
            struct sockaddr_in addr;
        
        public:
            MySocket(int, sa_family_t, in_port_t, in_addr_t);
            void listener();
            void sender(const std::string);
            ~MySocket();
    };
}
