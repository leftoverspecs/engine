#pragma once

#include <GL/glew.h>

#include <optional>

namespace engine::opengl {

class VertexArray {
public:
    class Binding {
    public:
        explicit Binding(const VertexArray &vao);
        ~Binding();

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
