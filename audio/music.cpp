#include "music.hpp"

#include <stdexcept>
#include <utility>

namespace engine::audio {

namespace {

std::function<void(const Music *)> current_finish_callback;
const Music *current_playing = nullptr;

void finish_callback() {
    if (current_finish_callback) {
        const auto playing = current_playing;
        current_playing = nullptr;
        current_finish_callback(playing);
    }
}

}

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

double Music::get_position() const {
    return Mix_GetMusicPosition(music);
}

void Music::fade_in(int loops, int ms) const {
    if (Mix_FadeInMusic(music, loops, ms) != 0) {
        throw std::runtime_error(SDL_GetError());
    }
    current_playing = this;
}

void Music::fade_out(int ms) {
    Mix_FadeOutMusic(ms);
}

void Music::set_finish_callback(std::function<void(const Music *)> callback) {
    if (callback) {
        current_finish_callback = std::move(callback);
        Mix_HookMusicFinished(finish_callback);
    } else {
        current_finish_callback = nullptr;
        Mix_HookMusicFinished(nullptr);
    }
}

void Music::set_volume(int volume) {
    Mix_VolumeMusic(volume);
}

}
