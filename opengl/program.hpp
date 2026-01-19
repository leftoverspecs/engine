#pragma once

#include "shader.hpp"

#include <GL/glew.h>
#include <glm/mat4x4.hpp>

#include <stdexcept>

namespace engine::opengl {

class Program {
public:
    class Exception : public std::runtime_error {
    public:
        explicit Exception(const char *message);
    };

    class Usage {
    public:
        explicit Usage(const Program &program);
        ~Usage();

        void set_uniform(const char *name, const glm::mat4x4 &m, bool transpose = false) const;
        void set_uniform(const char *name, const glm::mat3x3 &m, bool transpose = false) const;
        void set_uniform(const char *name, const glm::mat2 &m, bool transpose = false) const;
        void set_uniform(const char *name, const glm::vec3 &v) const;
        void set_uniform(const char *name, const glm::vec4 &v) const;
        void set_uniform(const char *name, GLint x) const;
        void set_uniform(const char *name, GLfloat x) const;

        Usage(Usage &&) = delete;
        Usage(const Usage &) = delete;
        Usage &operator = (Usage &&) = delete;
        Usage &operator = (const Usage &) = delete;
    private:
        const Program *program;
    };

    Program();
    ~Program();

    void bind(GLuint index, const GLchar *name) const;
    void attach(const Shader &) const;
    void link() const;
    [[nodiscard]] Usage use() const;

    void uniform_block_binding(const GLchar *name, GLuint uniformBlockBinding) const;

    Program(const Program &) = delete;
    Program &operator = (const Program &) = delete;
private:
    GLuint id;
};

}
