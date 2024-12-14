#include "initialize.hpp"

#include <SDL2/SDL.h>
#include <stdexcept>

namespace engine::sdl {

initialize::initialize(uint32_t flags) {
    const int result = SDL_Init(flags);
    if (result != 0) {
        throw std::runtime_error(std::string("Can't initialize SDL2_Net: ") + SDL_GetError());
    }
}
initialize::~initialize() {
    SDL_Quit();
}

}
