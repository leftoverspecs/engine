#pragma once

#include "destination.hpp"

namespace engine::opengl {

class Screen {
public:
    Screen(float screen_width, float screen_height);

    void shaking();
    void colorize(glm::vec3 color);

    void switch_fullscreen(int display_id, bool fullscreen);

    Framebuffer::Binding bind_as_target();

    void update(float msec);
    void draw();
private:
    Destination destination;
    float time;

    float shake;
    glm::vec2 position;
    glm::vec3 color;

    float window_x;
    float window_y;
    float window_width;
    float window_height;
};

}
