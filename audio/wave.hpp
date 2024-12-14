#pragma once

#include <SDL.h>

#include <string>
#include <vector>

namespace engine {

class Wave {
public:
    explicit Wave(const std::string &filename);
    explicit Wave(const unsigned char *data, std::size_t size);
    ~Wave();

    Wave(const Wave &) = delete;
    Wave &operator = (const Wave &) = delete;

    [[nodiscard]] const SDL_AudioSpec &get_spec() const;
    [[nodiscard]] const Uint8 *get_buffer() const;
    [[nodiscard]] Uint32 get_length() const;

    [[nodiscard]] std::vector<Uint8> convert_to_spec(const SDL_AudioSpec &destination) const;
private:
    SDL_AudioSpec spec{};
    Uint8 *buffer{nullptr};
    Uint32 length{0};

    Wave(const SDL_AudioSpec &spec, Uint8 *buffer, Uint32 length);
};

}
