#include "screen.hpp"

#include <glm/gtx/transform.hpp>

#include <SDL.h>

namespace engine::opengl {

Screen::Screen(float screen_width, float screen_height)
  : destination(screen_width, screen_height),
    window_x(0),
    window_y(0),
    window_width(screen_width),
    window_height(screen_height)
{
    destination.set_exposure(3.2f);
    destination.set_gamma(0.6f);
}

void Screen::switch_fullscreen(int display_id, bool fullscreen) {
    if (fullscreen) {
        SDL_DisplayMode mode;
        SDL_GetCurrentDisplayMode(display_id, &mode);
        const float game_aspect_ratio = static_cast<float>(destination.get_screen_width()) / destination.get_screen_height();
        const float display_aspect_ratio = static_cast<float>(mode.w) / mode.h;
        if (display_aspect_ratio > game_aspect_ratio) {
            window_height = mode.h;
            window_width = window_height * game_aspect_ratio;
            window_x = (mode.w - window_width) / 2;
            window_y = 0;
        } else if (display_aspect_ratio < game_aspect_ratio) {
            window_width = mode.w;
            window_height = window_width / game_aspect_ratio;
            window_x = 0;
            window_y = (mode.h - window_height) / 2;
        } else {
            window_width = mode.w;
            window_width = mode.h;
        }
    } else {
        window_width = destination.get_screen_width();
        window_height = destination.get_screen_height();
        window_x = 0;
        window_y = 0;
    }
}

Framebuffer::Binding Screen::bind_as_target() {
    return destination.bind_as_target();
}

void Screen::draw(glm::vec4 tint) {
    draw(glm::translate(glm::vec3(0.0f, 0.0f, 0.0f)), tint);
}

void Screen::draw(glm::mat4x4 projection, glm::vec4 tint) {
    glViewport(window_x, window_y, window_width, window_height);
    destination.draw(projection, tint);
}

}
