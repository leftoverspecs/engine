#include "surface.hpp"

namespace engine::sdl {

Surface::Surface(SDL_Surface *surface) : surface{surface} {}

Surface::~Surface() {
    SDL_FreeSurface(surface);
}

SDL_Surface *Surface::get_surface() const {
    return surface;
}

Surface::operator bool() const {
    return surface != nullptr;
}

int Surface::get_width() const {
    return surface->w;
}

int Surface::get_height() const {
    return surface->h;
}

void *Surface::get_pixels() const {
    return surface->pixels;
}

}// namespace engine::sdl
