#include "music.hpp"

#include <stdexcept>

namespace engine::audio {

Music::Music(const unsigned char *data, std::size_t size)
  : music(Mix_LoadMUS_RW(SDL_RWFromConstMem(data, static_cast<int>(size)), 1))
{
    if (music == nullptr) {
        throw std::runtime_error(SDL_GetError());
    }
}

Music::~Music() {
    Mix_FreeMusic(music);
}

void Music::fade_in(int loops, int ms) const {
    if (Mix_FadeInMusic(music, loops, ms) != 0) {
        throw std::runtime_error(SDL_GetError());
    }
}

void Music::fade_out(int ms) {
    Mix_FadeOutMusic(ms);
}

void Music::set_volume(int volume) {
    Mix_VolumeMusic(volume);
}

}
