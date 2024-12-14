#pragma once

#include <GL/glew.h>

namespace engine::opengl {

class Renderbuffer {
public:
    class Binding {
    public:
        ~Binding();

        void storage(GLenum internalformat, GLsizei width, GLsizei height) const;

        Binding(Binding &&) = delete;
        Binding(const Binding &) = delete;
        Binding &operator = (const Binding &) = delete;
        Binding &operator = (Binding &&) = delete;
    private:
        friend class Renderbuffer;
        Binding(GLenum target, const Renderbuffer &renderbuffer);
        GLenum target;
    };
    Renderbuffer();
    ~Renderbuffer();

    [[nodiscard]] GLuint get_id() const { return id; }

    [[nodiscard]] Binding bind(GLenum target) const;

    Renderbuffer(const Renderbuffer &) = delete;
    Renderbuffer &operator = (const Renderbuffer &) = delete;
private:
    GLuint id;
};

}
