#include "model.h"

#include "shader.hpp"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <map>
#include <sstream>
#include <string>
#include <vector>

#include <opengl/model.vert.h>
#include <opengl/model.frag.h>

namespace engine::opengl {

Model::ParseError::ParseError(const std::string &message) : std::runtime_error(message) {}

namespace {
std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> parts;
    std::istringstream iss(s);
    std::string token;
    while (getline(iss, token, delimiter)) {
        parts.push_back(token);
    }
    return parts;
}

}

Model::Model(const char *source, std::size_t length) {
    {
        std::istringstream iss(std::string(source, length));
        std::string line;
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> vertex_normals;
        std::vector<glm::vec2> texture_coords;
        std::map<std::tuple<unsigned int, unsigned int, unsigned int>, unsigned int> points;
        std::vector<float> data;
        std::vector<unsigned int> elements;
        while (std::getline(iss, line)) {
            if (line.empty() || line[0] == '#') {
                continue;
            }
            const std::vector<std::string> parts = split(line, ' ');
            if (parts.empty()) {
                continue;
            }
            const std::string &command = parts[0];
            if (command == "v") {
                if (parts.size() != 1 + 3) {
                    throw ParseError("Vertices must have exactly three components");
                }
                vertices.emplace_back(std::stof(parts[1]), std::stof(parts[2]), std::stof(parts[3]));
            } else if (command == "vn") {
                if (parts.size() != 1 + 3) {
                    throw ParseError("Vertex normals must have exactly three components");
                }
                vertex_normals.emplace_back(std::stof(parts[1]), std::stof(parts[2]), std::stof(parts[3]));
            } else if (command == "vt") {
                if (parts.size() != 1 + 2) {
                    throw ParseError("Texture coordinates must have exactly two components");
                }
                texture_coords.emplace_back(std::stof(parts[1]), std::stof(parts[2]));
            } else if (command == "f") {
                if (parts.size() != 1 + 3) {
                    throw ParseError("Faces must be triangles");
                }
                for (int i = 1; i < parts.size(); ++i) {
                    const auto indices = split(parts[i], '/');
                    if (indices.size() != 3) {
                        throw ParseError("Face vertex indices must reference a vertex, a normal vector and a texture coordinate");
                    }
                    const std::size_t vi = std::stoi(indices[0]);
                    const glm::vec3 &v = vertices.at(vi - 1);
                    const std::size_t vti = std::stoi(indices[1]);
                    const glm::vec2 &vt = texture_coords.at(vti - 1);
                    const std::size_t vni = std::stoi(indices[2]);
                    const glm::vec3 &vn = vertex_normals.at(vni - 1);
                    const std::tuple<unsigned int, unsigned int, unsigned int> p{ vi, vti, vni };
                    const auto it = points.find(p);
                    if (it == points.end()) {
                        data.push_back(v.x);
                        data.push_back(v.y);
                        data.push_back(v.z);
                        data.push_back(vn.x);
                        data.push_back(vn.y);
                        data.push_back(vn.z);
                        data.push_back(vt.x);
                        data.push_back(vt.y);
                        unsigned int index = data.size() / 8 - 1;
                        elements.push_back(index);
                        points.emplace(p, index);
                    } else {
                        elements.push_back(it->second);
                    }
                }
            }
        }
        num_elements = elements.size();

        const auto vao_binding = vao.bind();
        {
            const auto vertex_buffer_binding = vertex_buffer.bind(GL_ARRAY_BUFFER);
            vertex_buffer_binding.data(static_cast<GLsizeiptr>(data.size() * sizeof(float)), data.data(), GL_STATIC_DRAW);
            vao_binding.vertex_attrib_pointer(vertex_buffer_binding, 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
            vao_binding.vertex_attrib_pointer(vertex_buffer_binding, 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
            vao_binding.vertex_attrib_pointer(vertex_buffer_binding, 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void *>(6 * sizeof(float)));
        }
        vao_binding.enable_attribute(0);
        vao_binding.enable_attribute(1);
        vao_binding.enable_attribute(2);

        const auto ebo = element_buffer.bind(GL_ELEMENT_ARRAY_BUFFER);
        ebo.data(static_cast<GLsizeiptr>(elements.size() * sizeof(unsigned int)), elements.data(), GL_STATIC_DRAW);
    }
    {
        shader.attach(Shader(GL_VERTEX_SHADER, reinterpret_cast<const char *>(model_vert), sizeof(model_vert)));
        shader.attach(Shader(GL_FRAGMENT_SHADER, reinterpret_cast<const char *>(model_frag), sizeof(model_frag)));
        shader.link();
    }
}

void Model::draw(const glm::vec3 &light,
              const glm::vec3 &lightColor,
              const glm::mat4 &projection,
              const glm::mat4 &view,
              const glm::mat4 &model,
              const glm::vec3 &color) const {
    const auto usage = shader.use();
    usage.set_uniform("view", view);
    usage.set_uniform("projection", projection);

    usage.set_uniform("lightPos", light);
    usage.set_uniform("lightColor", lightColor);
    usage.set_uniform("objectColor", color);
    usage.set_uniform("model", model);

    const glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(model)));
    usage.set_uniform("normalMatrix", normalMatrix);

    auto vao_bind = vao.bind();
    const auto ebo = element_buffer.bind(GL_ELEMENT_ARRAY_BUFFER);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(num_elements), GL_UNSIGNED_INT, nullptr);
}

} // namespace engine
