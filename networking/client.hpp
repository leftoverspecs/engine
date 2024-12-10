#pragma once

#include <cstdint>
#include <string>
#include <stdexcept>
#include <vector>

#include <SDL_net.h>

namespace engine::networking {

class Client {
public:
    class exception : public std::runtime_error {
    public:
        explicit exception(const std::string &message);
    };

    Client(const std::string &hostname, uint16_t port);
    ~Client();

    std::vector<uint8_t> send(const std::vector<uint8_t> &m) const;
private:
    TCPsocket socket;
};

}
