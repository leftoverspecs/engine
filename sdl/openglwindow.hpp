#pragma once
#include "window.hpp"

namespace engine::sdl {

class OpenGlWindow {
public:
    OpenGlWindow(const char *title,
                 int x, int y, int w,
                 int h, Uint32 flags);
    ~OpenGlWindow();

    void swap_window() const;

private:
    class OpenGlAttributes {
    public:
        OpenGlAttributes();
    };

    OpenGlAttributes glAttributes;
    Window window;
    SDL_GLContext context;
};

}// namespace engine::sdl
// engine
