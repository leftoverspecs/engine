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

void Window::set_title(const char *title) const {
    SDL_SetWindowTitle(window, title);
}

void Window::set_fullscreen(Uint32 flags) const {
    SDL_SetWindowFullscreen(window, flags);
}

void Window::set_icon(const graphics::Image &icon) const {
    SDL_SetWindowIcon(window, icon.get_surface().get_surface());
}

int Window::get_window_display_index() const {
    return SDL_GetWindowDisplayIndex(window);
}

}// namespace engine::sdl
