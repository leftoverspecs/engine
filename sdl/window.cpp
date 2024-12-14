#include "window.hpp"

#include <stdexcept>

namespace engine::sdl {

Window::Window(const char *title, int x, int y, int w, int h, Uint32 flags)
    : window(SDL_CreateWindow(title, x, y, w, h, flags))
{
    if (window == nullptr) {
        throw std::runtime_error("failed to create window");
    }
}

Window::~Window() {
    SDL_DestroyWindow(window);
}

SDL_Window *Window::get_window() const {
    return window;
}

}
