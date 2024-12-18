#pragma once

#include <SDL_net.h>

#include <cstdint>
#include <vector>

namespace engine::networking {

std::vector<uint8_t> receive(TCPsocket source);

void send(TCPsocket destination, const std::vector<uint8_t> &m);

}
