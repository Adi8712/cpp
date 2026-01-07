#include "core/core.hpp"
#include <atomic>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>
#include <vector>

int main() {
    core::MySocket server(DOMAIN, SOCKTYPE);
    core::MySocket client(DOMAIN, SOCKTYPE);
    
    std::thread listen([&server]() {
        server.listener();
    });

    std::vector<std::string> words = {"In diam massa varius volutpat consequat, sit justo at fermentum.", "Neque posuere imperdiet diam at leo ultricies placerat eu sollicitudin.", "Sem varius himenaeos inceptos nascetur consectetur integer in laoreet mauris.", "Donec maecenas, consectetur primis et himenaeos ipsum pretium per vehicula?", "Varius tellus torquent suscipit, penatibus nisi suspendisse congue purus magnis."};

    for(std::string s : words) {
        client.sender(s);
        sleep(1);
    }
    
    core::run = false;
    client.sender("Kill Switch");
    listen.join();

    return 0;
}
