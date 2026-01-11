#include "core/core.hpp"
#include "utils/utils.hpp"
#include <chrono>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

int main(int argc, char* argv[]) {
    const utils::Config& cfg = utils::ArgParser(argc, argv).config();
    
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
            
            while (true) {
                long now = std::chrono::system_clock::now().time_since_epoch().count();
                
                client.sender(std::to_string(now));
                std::cout << "Sent at: " << now << "\n";
                
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
            break;
        }
        
        case utils::BOTH:
        {
            
            break;
        }
    }

    return 0;
}
