#include "transmit.hpp"

#include <stdexcept>

namespace engine::networking {

std::vector<uint8_t> receive(TCPsocket source) {
    std::vector<uint8_t> result;
    std::vector<uint8_t> chunk(1024);
    int received = 0;
    do {
        received = SDLNet_TCP_Recv(source, chunk.data(), static_cast<int>(chunk.size()));
        if (received < 0) {
            throw std::runtime_error(std::string("Can't receive data: ") + SDLNet_GetError());
        }
        if (received > 0) {
            result.insert(result.end(), chunk.begin(), chunk.begin() + received);
        }
    } while (received == 0);
    return result;
}

void send(TCPsocket destination, const std::vector<uint8_t> &m) {
    int sent = SDLNet_TCP_Send(destination, m.data(), static_cast<int>(m.size()));
    if (sent < m.size()) {
        throw std::runtime_error(std::string("Can't send data: ") + SDLNet_GetError());
    }
}

}
