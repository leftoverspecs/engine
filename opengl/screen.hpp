#pragma once

#include "destination.hpp"

namespace engine::opengl {

class Screen {
public:
    Screen(float screen_width, float screen_height);

    void switch_fullscreen(int display_id, bool fullscreen);

    Framebuffer::Binding bind_as_target();

    void draw(glm::vec4 tint);
    void draw(glm::mat4x4 projection, glm::vec4 tint);
private:
    Destination destination;
    float window_x;
    float window_y;
    float window_width;
    float window_height;
};

}
