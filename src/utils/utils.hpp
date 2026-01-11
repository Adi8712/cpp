#pragma once

#include <arpa/inet.h>
#include <netinet/in.h>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <sys/socket.h>

namespace utils {
    enum ProgStat {
        LISTENER,
        SENDER,
        BOTH
    };
    
    namespace {    
        struct Target {
            in_addr_t addr;
            in_port_t port;
        };
    }
    
    struct Config {
        std::optional<in_port_t> listen_port;
        std::optional<Target> send_to;
        
        ProgStat status;
    };
    
    class ArgParser {
        private:
            Config cfg_;
        
        public:
            explicit ArgParser(int, char* []);
            
            [[nodiscard]] const Config& config() const& noexcept;
    };
}