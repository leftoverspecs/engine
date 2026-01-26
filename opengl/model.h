#ifndef ENGINE_OPENGL_MODEL_H
#define ENGINE_OPENGL_MODEL_H

#include "buffer.hpp"
#include "program.hpp"
#include "vertexarray.hpp"

#include <stdexcept>

namespace engine::opengl {

class Model {
public:
    class ParseError : public std::runtime_error {
    public:
        explicit ParseError(const std::string& message);
    };

    Model(const char *source, std::size_t length);

    void draw(const glm::vec3 &light,
              const glm::vec3 &lightColor,
              const glm::mat4 &projection,
              const glm::mat4 &view,
              const glm::mat4 &model,
              const glm::vec3 &color) const;

private:
    unsigned int num_elements;
    VertexArray vao;
    Buffer vertex_buffer;
    Buffer element_buffer;
    Program shader;
};

} // namespace engine

#endif //ENGINE_OPENGL_MODEL_H
