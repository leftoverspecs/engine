#include "spritemap.hpp"

#include <graphics/image.hpp>

#include <SDL.h>

#include <stdexcept>

namespace engine::opengl {

SpriteMap::SpriteMap(const unsigned char *png, std::size_t size,
                     unsigned int columns, unsigned int rows)
  : columns(static_cast<GLfloat>(columns)),
    rows(static_cast<GLfloat>(rows))
{
    graphics::Image image(png, size);
    const sdl::Surface &surface = image.get_surface();

    auto binding = bind(GL_TEXTURE0, GL_TEXTURE_2D);
    //binding.set_parameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
    //binding.set_parameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
    binding.set_parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    binding.set_parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    binding.set_parameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    binding.set_parameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    binding.image_2d(0, GL_RGBA, surface.get_width(), surface.get_height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, surface.get_pixels());

    sprite_width = static_cast<GLfloat>(surface.get_width()) / static_cast<GLfloat>(columns);
    sprite_height = static_cast<GLfloat>(surface.get_height()) / static_cast<GLfloat>(rows);
}

Texture::Binding SpriteMap::bind(GLenum texture_unit, GLenum target) const {
    return texture.bind(texture_unit, target);
}

SpriteMap::TextureRect SpriteMap::get_sprite(unsigned int i, unsigned j) const {
    return get_sprite(i, j, 1, 1);
}

SpriteMap::TextureRect SpriteMap::get_sprite(unsigned int i, unsigned j, unsigned w, unsigned h) const {
    const auto fi = static_cast<GLfloat>(i);
    const auto fj = static_cast<GLfloat>(j);
    const auto fw = static_cast<GLfloat>(w);
    const auto fh = static_cast<GLfloat>(h);
    return TextureRect { fi / columns, fj / rows,
                        (fi + fw) / columns, (fj + fh) / rows };
}

}
