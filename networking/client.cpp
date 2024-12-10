#include "client.hpp"
#include "transmit.hpp"

#include <stdexcept>

namespace engine::networking {

Client::exception::exception(const std::string &message)
    : std::runtime_error(message + ": " + SDLNet_GetError())
{}

Client::Client(const std::string &hostname, uint16_t port) {
    IPaddress address;
    if (SDLNet_ResolveHost(&address, hostname.c_str(), port) == -1) {
        throw exception("Can't resolve host \"" + hostname + ':' + std::to_string(port) + '"');
    }
    socket = SDLNet_TCP_Open(&address);
    if (socket == nullptr) {
        throw exception("Can't open connection to host \"" + hostname + ':' + std::to_string(port) + '"');
    }
}

Client::~Client() {
    SDLNet_TCP_Close(socket);
}

std::vector<uint8_t> Client::send(const std::vector<uint8_t> &m) const {
    engine::networking::send(socket, m);
    return receive(socket);
}

}
