#include "core/core.hpp"
#include "utils/utils.hpp"
#include <chrono>
#include <cstdio>
#include <mutex>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

int main(int argc, char* argv[]) {
    const utils::Config cfg = utils::ArgParser(argc, argv).config();

    switch (cfg.status) {
        case utils::LISTENER:
        {
            core::MySocket server(DOMAIN, SOCKTYPE, cfg.listen_port.value(), INADDR_ANY);
            server.listener();

            break;
        }

        case utils::SENDER:
        {
            core::MySocket client(DOMAIN, SOCKTYPE, cfg.send_to->port, cfg.send_to->addr);
            client.sender();

            break;
        }

        case utils::BOTH:
        {
            core::MySocket server(DOMAIN, SOCKTYPE, cfg.listen_port.value(), INADDR_ANY);
            core::MySocket client(DOMAIN, SOCKTYPE, cfg.send_to->port, cfg.send_to->addr);

            std::jthread listen([&server]() {
                server.listener();
            });

            {
                std::unique_lock<std::mutex> lock(core::MySocket::mtx);
                core::MySocket::cv.wait(lock, [] { return core::MySocket::run;});
            }

            client.sender();

            break;
        }
    }

    return 0;
}
