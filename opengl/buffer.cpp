#include "buffer.hpp"

namespace engine::opengl {

Buffer::Binding::Binding(GLenum target, const Buffer &buffer)
  : target(target)
{
    glBindBuffer(target, buffer.get_id());
}

Buffer::Binding::~Binding() {
    glBindBuffer(target, 0);
}

void Buffer::Binding::data(GLsizeiptr size, const void *data, GLenum usage) const {
    glBufferData(target, size, data, usage);
}

void Buffer::Binding::subdata(GLintptr offset, GLsizeiptr size, const void *data) const {
    glBufferSubData(target, offset, size, data);
}

Buffer::Buffer() {
    glGenBuffers(1, &id);
}

Buffer::~Buffer() {
    glDeleteBuffers(1, &id);
}

Buffer::Binding Buffer::bind(GLenum target) const {
    return {target, *this};
}

void Buffer::bind_buffer_base(GLenum target, GLuint index) const {
    glBindBufferBase(target, index, id);
}

}// namespace engine::opengl
