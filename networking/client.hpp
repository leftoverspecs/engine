#pragma once

#include <cstdint>
#include <string>
#include <stdexcept>
#include <vector>

#include <SDL_net.h>

namespace engine::networking {

class client {
public:
    class exception : public std::runtime_error {
    public:
        explicit exception(const std::string &message);
    };

    client(const std::string &hostname, uint16_t port);
    ~client();

    client(const client &other) = delete;
    client &operator=(const client &other) = delete;

    [[nodiscard]] std::vector<uint8_t> send(const std::vector<uint8_t> &m) const;
private:
    TCPsocket socket;
};

}
