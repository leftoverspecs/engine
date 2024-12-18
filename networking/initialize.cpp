#include "initialize.hpp"

#include <SDL_net.h>
#include <stdexcept>

namespace engine::networking {

initialize::initialize(const sdl::initialize &) {
    const int result = SDLNet_Init();
    if (result != 0) {
        throw std::runtime_error(std::string("Can't initialize SDL2_Net: ") + SDLNet_GetError());
    }
}

initialize::~initialize() {
    SDLNet_Quit();
}

}
