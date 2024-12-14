#include "destination.hpp"

#include <opengl/destination.vert.h>
#include <opengl/destination.frag.h>

namespace engine::opengl {

namespace {

GLfloat screen_vertex_data[] = {
        /*   X      Y     S     T    */
        -2.0f, -2.0f, -0.5f, -0.5f,
        -2.0f, 2.0f, -0.5f, 1.5f,
        2.0f, 2.0f, 1.5f, 1.5f,

        -2.0f, -2.0f, -0.5f, -0.5f,
        2.0f, 2.0f, 1.5f, 1.5f,
        2.0f, -2.0f, 1.5f, -0.5f};

constexpr int ATTRIBUTE_POSITION = 0;
constexpr int ATTRIBUTE_TEXTURE_COORD = 1;

}

Destination::Destination(GLsizei screen_width, GLsizei screen_height)
  : screen_width(screen_width),
    screen_height(screen_height),
    gamma(0.2f),
    exposure(4.0f)
{
    shader.attach(Shader(GL_VERTEX_SHADER, reinterpret_cast<const char *>(destination_vert), sizeof(destination_vert)));
    shader.attach(Shader(GL_FRAGMENT_SHADER, reinterpret_cast<const char *>(destination_frag), sizeof(destination_frag)));
    shader.bind(ATTRIBUTE_POSITION, "position");
    shader.bind(ATTRIBUTE_TEXTURE_COORD, "texture_coord");
    shader.link();

    {
        auto binding = vao.bind();
        binding.enable_attribute(ATTRIBUTE_POSITION);
        binding.enable_attribute(ATTRIBUTE_TEXTURE_COORD);

        auto buffer_binding = screen_vertices.bind(GL_ARRAY_BUFFER);
        buffer_binding.vertex_attrib_pointer(binding, ATTRIBUTE_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, reinterpret_cast<void *>(0 * sizeof(float)));
        buffer_binding.vertex_attrib_pointer(binding, ATTRIBUTE_TEXTURE_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, reinterpret_cast<void *>(2 * sizeof(float)));
        buffer_binding.data(sizeof(screen_vertex_data), screen_vertex_data, GL_STATIC_DRAW);
    }
    {
        auto binding = destination.bind(GL_TEXTURE0, GL_TEXTURE_2D);
        binding.image_2d(0, GL_RGB16F, screen_width, screen_height, 0, GL_RGBA, GL_FLOAT, nullptr);
        binding.set_parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        binding.set_parameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        binding.set_parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        binding.set_parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    {
        auto binding = depth_stencil.bind(GL_RENDERBUFFER);
        binding.storage(GL_DEPTH24_STENCIL8, screen_width, screen_height);
    }
    {
        auto binding = framebuffer.bind(GL_FRAMEBUFFER);
        binding.attach(GL_COLOR_ATTACHMENT0, destination, 0);
        binding.attach(GL_DEPTH_STENCIL_ATTACHMENT, depth_stencil);
        if (binding.get_status() != GL_FRAMEBUFFER_COMPLETE) {
            throw Exception("Destination framebuffer not complete");
        }
    }
}

Framebuffer::Binding Destination::bind_as_target() const {
    glViewport(0, 0, screen_width, screen_height);
    return framebuffer.bind(GL_FRAMEBUFFER);
}

void Destination::set_gamma(float gamma) {
    this->gamma = gamma;
}

void Destination::set_exposure(float exposure) {
    this->exposure = exposure;
}

void Destination::draw(const glm::mat4x4 &projection, const glm::vec3 &effect, float alpha, const glm::vec3 &factor) const {
    auto usage = shader.use();
    usage.set_uniform("projection", projection);
    usage.set_uniform("effect", effect);
    usage.set_uniform("alpha", alpha);
    usage.set_uniform("factor", factor);
    usage.set_uniform("gamma", gamma);
    usage.set_uniform("exposure", exposure);
    auto binding = vao.bind();
    auto destination_texture_binding = destination.bind(GL_TEXTURE0, GL_TEXTURE_2D);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(screen_vertex_data) / 4);
}

GLsizei Destination::get_screen_width() const {
    return screen_width;
}

GLsizei Destination::get_screen_height() const {
    return screen_height;
}

}
