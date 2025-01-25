#pragma once

#include "texture.hpp"
#include <cstddef>

namespace engine::opengl {

class SpriteMap {
public:
    SpriteMap(const unsigned char *png, std::size_t size,
              unsigned int columns, unsigned int rows);

    [[nodiscard]] Texture::Binding bind(GLenum texture_unit, GLenum target) const;

    struct TextureRect {
        GLfloat u_min;
        GLfloat v_min;
        GLfloat u_max;
        GLfloat v_max;
    };

    [[nodiscard]] TextureRect get_sprite(unsigned int i, unsigned j) const;
    [[nodiscard]] TextureRect get_sprite(unsigned int i, unsigned j, unsigned w, unsigned h) const;

    [[nodiscard]] GLfloat get_sprite_width() const { return sprite_width; }
    [[nodiscard]] GLfloat get_sprite_height() const { return sprite_height; }
private:
    Texture texture;
    GLfloat sprite_width;
    GLfloat sprite_height;
    GLfloat columns;
    GLfloat rows;
};

}
