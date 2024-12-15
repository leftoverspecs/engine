#pragma once

namespace engine::sdl {

class initialize;

}

namespace engine::networking {

class initialize {
public:
    explicit initialize(const sdl::initialize &);
    ~initialize();
};

}
