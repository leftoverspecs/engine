#pragma once

#include "buffer.hpp"
#include "program.hpp"
#include "vertexarray.hpp"

#include <vector>

namespace engine::opengl {

class BoxRenderer {
public:
    BoxRenderer(float screen_width, float screen_height);

    void clear();
    void queue_frame(const glm::mat4 &model, const glm::vec4 &color);
    void draw();
private:
    Program shader;
    VertexArray vao;
    Buffer vertex_buffer;
    std::vector<GLfloat> batch;
};

}// namespace engine::opengl
