#include "image.hpp"

#include <SDL2/SDL_image.h>

#include <stdexcept>

namespace engine::graphics {

Image::Image(const unsigned char *data, std::size_t size)
    : surface(IMG_LoadTyped_RW(SDL_RWFromConstMem(data, static_cast<int>(size)), 1, "PNG")) {
    if (!surface) {
        throw std::runtime_error(SDL_GetError());
    }
}

}
