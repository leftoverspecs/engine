#pragma once

#include "buffer.hpp"
#include "framebuffer.hpp"
#include "program.hpp"
#include "renderbuffer.hpp"
#include "texture.hpp"
#include "vertexarray.hpp"

#include <glm/mat4x4.hpp>

#include <stdexcept>

namespace engine::opengl {

class Destination {
public:
    class Exception : public std::runtime_error {
    public:
        explicit Exception(const char *message) : std::runtime_error(message) { }
    };

    Destination(GLsizei screen_width, GLsizei screen_height);

    [[nodiscard]] Framebuffer::Binding bind_as_target() const;

    void draw(const glm::mat4x4 &projection, const glm::vec4 &tint) const;

    void set_gamma(float gamma);
    void set_exposure(float exposure);

    [[nodiscard]] float get_gamma() const { return gamma; }
    [[nodiscard]] float get_exposure() const { return exposure; }

    [[nodiscard]] GLsizei get_screen_width() const;
    [[nodiscard]] GLsizei get_screen_height() const;

private:
    Program shader;
    GLsizei screen_width;
    GLsizei screen_height;
    Framebuffer framebuffer;
    Texture destination;
    Renderbuffer depth_stencil;
    VertexArray vao;
    Buffer screen_vertices;
    float gamma;
    float exposure;
};

}
