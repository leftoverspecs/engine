#pragma once

#include <SDL_surface.h>

namespace engine::sdl {

class Surface {
public:
    explicit Surface(SDL_Surface *surface);
    ~Surface();

    Surface(const Surface &) = delete;
    Surface &operator=(const Surface &) = delete;

    [[nodiscard]] SDL_Surface *get_surface() const;

    explicit operator bool() const;
    [[nodiscard]] int get_width() const;
    [[nodiscard]] int get_height() const;
    [[nodiscard]] void *get_pixels() const;
private:
    SDL_Surface* surface{nullptr};
};

}
