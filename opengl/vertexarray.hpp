#pragma once

#include "buffer.hpp"

#include <GL/glew.h>

namespace engine::opengl {

class VertexArray {
public:
    class Binding {
    public:
        explicit Binding(const VertexArray &vao);
        ~Binding();

        void vertex_attrib_pointer(const Buffer::Binding &, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer) const;
        void enable_attribute(GLuint index) const;

        Binding(Binding &&) = delete;
        Binding(const Binding &) = delete;
        Binding &operator = (const Binding &) = delete;
        Binding &operator = (Binding &&) = delete;
    private:
        bool bound;
    };

    VertexArray();
    ~VertexArray();

    [[nodiscard]] Binding bind() const;

    VertexArray(const VertexArray &) = delete;
    VertexArray &operator = (const VertexArray &) = delete;
private:
    GLuint id{0};
};

}
