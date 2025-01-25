#pragma once

namespace engine::sdl {

class initialize;

}

namespace engine::audio {

class initialize {
public:
    explicit initialize(const sdl::initialize &, int flags);
    ~initialize();
};

}
