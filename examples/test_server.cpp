#include "message.hpp"


#include <csignal>
#include <iomanip>
#include <networking/initialize.hpp>
#include <networking/server.hpp>
#include <sdl/initialize.hpp>

#include <iostream>

namespace {

bool running = true;

void sigint_handler(int ignore) {
    running = false;
}

}// namespace

class test_handler : public engine::networking::handler {
public:
    std::vector<uint8_t> receive(int id, const std::vector<uint8_t> &data) override {
        const Message message = decode_message(data);
        std::cout << "Received: Message { name = \"" << message.name() << "\", age = " << message.age() << " }\n";
        return {};
    }

    bool idle() override { return running; }
};

int main() {
    signal(SIGINT, sigint_handler);

    engine::sdl::initialize sdl(SDL_INIT_EVERYTHING);
    engine::networking::initialize sdlnet(sdl);

    engine::networking::server s(10000, 10);
    test_handler h;
    s.run(1000, h);

    return 0;
}
