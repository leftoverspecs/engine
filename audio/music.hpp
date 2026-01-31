#pragma once

#include <SDL_mixer.h>

#include <cstddef>

namespace engine::audio {

class Music {
public:
    Music(const unsigned char *data, std::size_t size);
    ~Music();

    Music(const Music &) = delete;
    Music &operator = (const Music &) = delete;

    [[nodiscard]] double get_position() const;

    void fade_in(int loops, int ms) const;
    static void fade_out(int ms);

    static void set_volume(int volume);
private:
    Mix_Music *music;
};

}
