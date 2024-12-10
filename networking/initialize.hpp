#pragma once

namespace engine::common {

class initialize;

}

namespace engine::networking {

class initialize {
public:
    explicit initialize(const common::initialize &);
    ~initialize();
};

}
