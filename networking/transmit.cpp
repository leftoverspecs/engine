#include "transmit.hpp"

#include "primitives.hpp"

#include <stdexcept>

namespace engine::networking {

namespace {

bool receive_at_least(std::vector<uint8_t> &output, TCPsocket source, size_t size) {
    std::vector<uint8_t> chunk(size);
    int overall = 0;
    int received = 0;
    do {
        received = SDLNet_TCP_Recv(source, chunk.data(), static_cast<int>(chunk.size()));
        if (received < 0) {
            throw std::runtime_error(std::string("Can't receive data: ") + SDLNet_GetError());
        }
        if (received == 0) {
            return false;
        }
        overall += received;
        output.insert(output.end(), chunk.begin(), chunk.begin() + received);
    } while (overall < size);
    return true;
}

}

std::vector<uint8_t> receive(TCPsocket source) {
    std::vector<uint8_t> chunk;
    if (!receive_at_least(chunk, source, sizeof(uint32_t))) {
        return {};
    }
    auto it = chunk.begin();
    const uint32_t size = read_uint32(it, chunk.end());
    if (size > 0) {
        std::vector<uint8_t> result;
        result.reserve(size);
        result.insert(result.end(), it, chunk.end());
        if (!receive_at_least(result, source, size - std::distance(it, chunk.end()))) {
            return {};
        }
        return result;
    }
    return {};
}

void send(TCPsocket destination, const std::vector<uint8_t> &m) {
    uint8_t size[sizeof(uint32_t)];
    uint8_t *it = size;
    write_uint32(it, m.size());
    int sent = SDLNet_TCP_Send(destination, size, sizeof(uint32_t));
    if (sent < sizeof(uint32_t)) {
        throw std::runtime_error(std::string("Can't send size: ") + SDLNet_GetError());
    }
    if (!m.empty()) {
        sent = SDLNet_TCP_Send(destination, m.data(), static_cast<int>(m.size()));
        if (sent < m.size()) {
            throw std::runtime_error(std::string("Can't send data: ") + SDLNet_GetError());
        }
    }
}

}
