#pragma once
#include "window.hpp"

namespace engine::graphics {
class Image;
}
namespace engine::sdl {

class OpenGlWindow {
public:
    OpenGlWindow(const char *title,
                 int x, int y, int w,
                 int h, Uint32 flags);
    ~OpenGlWindow();

    void swap_window() const;
    void set_title(const char *title) const;
    void set_fullscreen(Uint32 flags) const;
    void set_icon(const graphics::Image &icon) const;
    [[nodiscard]] int get_window_display_index() const;

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
