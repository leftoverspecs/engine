#pragma once

#include <GL/glew.h>

#include <stdexcept>

namespace engine::opengl {

class Shader {
public:
    class Exception : public std::runtime_error {
    public:
        explicit Exception(const char *message);
    };

    explicit Shader(GLenum type, const char *source);
    explicit Shader(GLenum type, const char *source, std::size_t length);
    ~Shader();

    Shader(Shader &&shader) noexcept;
    Shader &operator = (Shader &&shader) noexcept;

    [[nodiscard]] GLuint get_id() const { return id; }

    Shader(const Shader &) = delete;
    Shader operator = (const Shader &) = delete;

private:
    GLuint id;
};

}
