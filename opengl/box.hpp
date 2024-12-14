#pragma once

#include "buffer.hpp"
#include "program.hpp"
#include "vertexarray.hpp"

namespace engine::opengl {

class Box {
public:
    Box(float x, float y, float w, float h, float screen_width, float screen_height);

    void relocate(float x, float y);
    void resize(float w, float h);

    bool collides_with_box(const Box &other) const;

    void draw(glm::vec4 color) const;
    void draw_filled(glm::vec4 color) const;

private:
    Program shader;
    VertexArray vao;
    Buffer vertex_buffer;
    
    float x;
    float y;
    float w;
    float h;
};

}
