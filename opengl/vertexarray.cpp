#include "vertexarray.hpp"

#include "buffer.hpp"

namespace engine::opengl {

VertexArray::Binding::Binding(const VertexArray &vao)
  : bound(true)
{
    glBindVertexArray(vao.id);
}

VertexArray::Binding::~Binding() {
    if (bound) {
        glBindVertexArray(0);
    }
}

void VertexArray::Binding::vertex_attrib_pointer(const Buffer::Binding &, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer) const {
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void VertexArray::Binding::enable_attribute(GLuint index) const {
    if (bound) {
        glEnableVertexAttribArray(index);
    }
}

VertexArray::VertexArray() {
    glGenVertexArrays(1, &id);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &id);
}

VertexArray::Binding VertexArray::bind() const {
    return Binding(*this);
}

}
