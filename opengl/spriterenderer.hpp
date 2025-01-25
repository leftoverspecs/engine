#pragma once

#include "buffer.hpp"
#include "program.hpp"
#include "spritemap.hpp"
#include "vertexarray.hpp"

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

#include <vector>

namespace engine::opengl {

class Texture;

class SpriteRenderer {
public:
    SpriteRenderer(const SpriteMap &map, GLfloat width, GLfloat height);

    void clear();
    void queue(const glm::mat4 &model, const glm::vec4 &color,
               unsigned int i, unsigned int j);
    void queue(const glm::mat4 &model, const glm::vec4 &color,
               unsigned int i, unsigned int j, unsigned int w, unsigned int h);
    void queue(const glm::mat4 &model, const glm::vec4 &color,
               const SpriteMap::TextureRect &rect);

    void draw(bool debug = false) const;
private:
    Program shader;
    VertexArray vao;
    Buffer vertex_buffer;
    const SpriteMap &map;
    std::vector<GLfloat> batch;
};

}
