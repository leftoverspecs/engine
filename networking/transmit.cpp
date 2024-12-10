#include "transmit.hpp"

#include <stdexcept>

namespace engine::networking {

std::vector<uint8_t> receive(TCPsocket source) {
    std::vector<uint8_t> buffer(1024);
    const int received = SDLNet_TCP_Recv(source, buffer.data(), static_cast<int>(buffer.size()));
    if (received <= 0) {
        throw std::runtime_error(std::string("Can't receive data: ") + SDLNet_GetError());
    } else {
        buffer.resize(received);
        auto pos = buffer.begin();
        return {pos, buffer.end()};
    }
}

void send(TCPsocket destination, const std::vector<uint8_t> &m) {
    int sent = SDLNet_TCP_Send(destination, m.data(), static_cast<int>(m.size()));
    if (sent < m.size()) {
        throw std::runtime_error(std::string("Can't send data: ") + SDLNet_GetError());
    }
}

}
