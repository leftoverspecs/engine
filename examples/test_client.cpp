#define SDL_MAIN_HANDLED
#include <iomanip>
#include <iostream>
#include <networking/client.hpp>
#include <numeric>

#include <sdl/initialize.hpp>
#include <networking/initialize.hpp>

#include "message.hpp"

#include <glm/ext/scalar_uint_sized.hpp>

int main() {
    engine::sdl::initialize sdl(SDL_INIT_EVERYTHING);
    engine::networking::initialize sdlnet(sdl);
    engine::networking::client c("localhost", 10000);
    Message message;
    message.set_name("Hello World!");
    message.set_age(10);
    std::vector<uint8_t> data(encode_message(message));
    std::vector<uint8_t> result(c.send(data));
    result = c.send({});
    return 0;
}
