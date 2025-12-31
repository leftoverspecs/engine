#pragma once

#include <GL/glew.h>

namespace engine::opengl {

class Buffer {
public:
    class Binding {
    public:
        Binding(GLenum target, const Buffer &buffer);
        ~Binding();

        void data(GLsizeiptr size, const void *data, GLenum usage) const;
        void subdata(GLintptr offset, GLsizeiptr size, const void *data) const;
    private:
        GLenum target;

    };

    Buffer();
    ~Buffer();

    [[nodiscard]] Binding bind(GLenum target) const;
    [[nodiscard]] GLuint get_id() const { return id; }

    void bind_buffer_base(GLenum target,
                          GLuint index) const;

    Buffer(const Buffer &) = delete;
    Buffer &operator = (const Buffer &) = delete;
private:
    GLuint id{0};
};

}
