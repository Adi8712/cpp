#include "core/core.hpp"
#include "utils/utils.hpp"
#include <atomic>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>
#include <unordered_map>
#include <vector>

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
            
            std::vector<std::string> words = {"In diam massa varius volutpat consequat, sit justo at fermentum.", "Neque posuere imperdiet diam at leo ultricies placerat eu sollicitudin.", "Sem varius himenaeos inceptos nascetur consectetur integer in laoreet mauris.", "Donec maecenas, consectetur primis et himenaeos ipsum pretium per vehicula?", "Varius tellus torquent suscipit, penatibus nisi suspendisse congue purus magnis."};
        
            for(std::string s : words) {
                client.sender(s);
                sleep(1);
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
