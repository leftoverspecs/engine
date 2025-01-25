#include "initialize.hpp"

#include <SDL_mixer.h>
#include <stdexcept>

namespace engine::audio {

initialize::initialize(const sdl::initialize &, int flags) {
    const int result = Mix_Init(flags);
    if (result != 0) {
        throw std::runtime_error(std::string("Can't initialize SDL2_Mixer: ") + Mix_GetError());
    }
}

initialize::~initialize() {
    Mix_Quit();
}

}
