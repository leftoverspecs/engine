#include "shader.hpp"

#include <cstring>
#include <vector>

namespace engine::opengl {

Shader::Exception::Exception(const char *message)
    : std::runtime_error(message) { }

Shader::Shader(GLenum type, const char *source)
  : Shader(type, source, strlen(source))
{ }

Shader::Shader(GLenum type, const char *source, std::size_t length)
  : id(glCreateShader(type))
{
    if (id == 0) {
        throw Exception("Can't create shader object");
    }
    const GLchar *const sources[] = { source };
    const GLint source_lengths[] = { static_cast<GLint>(length) };
    glShaderSource(id, 1, sources, source_lengths);
    glCompileShader(id);

    GLint status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint len = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        std::vector<char> buffer(len);
        glGetShaderInfoLog(id, len, nullptr, buffer.data());
        throw Exception(buffer.data());
    }
}

Shader::~Shader() {
    if (id != 0) {
        glDeleteShader(id);
    }
}

Shader::Shader(Shader &&shader) noexcept
    : id(shader.id)
{
    shader.id = 0;
}

Shader &Shader::operator = (Shader &&shader) noexcept {
    id = shader.id;
    shader.id = 0;
    return *this;
}

}
