#pragma once

#include <GL/glew.h>

namespace engine::opengl {

class Texture {
public:
    class Binding {
    public:
        ~Binding();

        void image_2d(GLint level, GLint internalformat, GLsizei width,
                      GLsizei height, GLint border, GLenum format,
                      GLenum type, const void *data) const;
        void set_parameter(GLenum pname, GLint param) const;
        void generate_mipmap() const;
        void clear(GLint level, GLenum format, GLenum type, const void *data) const;

        Binding(const Binding &) = delete;
        Binding(Binding &&) = delete;
        Binding &operator = (const Binding &) = delete;
        Binding &operator = (Binding &&) = delete;
    private:
        friend class Texture;
        Binding(GLenum texture_unit, GLenum target, const Texture &texture);

        GLenum texture_unit;
        GLenum target;
    };

    Texture();
    ~Texture();

    [[nodiscard]] Binding bind(GLenum texture_unit, GLenum target) const;

    [[nodiscard]] GLuint get_id() const { return id; }

    Texture(const Texture &) = delete;
    Texture &operator = (const Texture &) = delete;
private:
    GLuint id{0};
};

}
