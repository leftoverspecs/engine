#pragma once

#include <cstdint>

namespace engine::sdl {

class initialize {
public:
    explicit initialize(uint32_t flags);
    ~initialize();
};

}
