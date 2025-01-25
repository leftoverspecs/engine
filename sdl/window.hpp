#pragma once

#include <SDL_video.h>

namespace engine::sdl {

class Window {
public:
    Window(const char *title,
           int x, int y, int w,
           int h, Uint32 flags);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    [[nodiscard]] SDL_Window* get_window() const;
    void set_title(const char * title) const;
    void set_fullscreen(Uint32 flags) const;
    int get_window_display_index() const;
private:
    SDL_Window *window{nullptr};
};

}// namespace engine::sdl
