#include "chunk.hpp"

#include <stdexcept>

namespace engine::audio {

Chunk::Chunk(const unsigned char *data, std::size_t size, int channel)
  : chunk(Mix_LoadWAV_RW(SDL_RWFromConstMem(data, static_cast<int>(size)), 1)), channel(channel)
{
    if (chunk == nullptr) {
        throw std::runtime_error(SDL_GetError());
    }
}

Chunk::Chunk(Chunk &&other) noexcept : chunk(other.chunk) {
    other.chunk = nullptr;
}

Chunk &Chunk::operator = (Chunk &&other) noexcept {
    chunk = other.chunk;
    other.chunk = nullptr;
    return *this;
}

Chunk::~Chunk() {
    if (chunk != nullptr) {
        Mix_FreeChunk(chunk);
    }
}

void Chunk::play(int loops) const {
    if (Mix_PlayChannel(channel, chunk, loops) == -1) {
        throw std::runtime_error(SDL_GetError());
    }
}

void Chunk::set_volume(int volume) const {
    Mix_VolumeChunk(chunk, volume);
}

}
