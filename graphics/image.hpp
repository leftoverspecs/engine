#pragma once

#include <sdl/surface.hpp>

#include <cstddef>

namespace engine::graphics {

class Image {
public:
    Image(const unsigned char *data, std::size_t size);

    [[nodiscard]] const sdl::Surface &get_surface() const { return surface; }
private:
    sdl::Surface surface;
};

}
