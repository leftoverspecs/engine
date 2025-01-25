#include "audio.hpp"

#include <SDL_mixer.h>

#include <stdexcept>

namespace engine::audio {

#ifndef WIN32
namespace {

class AlsaEnv {
public:
    AlsaEnv() {
#ifndef WIN32
        setenv("ALSA_CONFIG_DIR", "/usr/share/alsa", 1);
#endif
    }
} alsa_env [[maybe_unused]];

}
#endif

Audio::Audio(int frequency, Uint16 format, int channels, int chunksize) {
    if (Mix_OpenAudio(frequency, format, channels, chunksize) != 0) {
        throw std::runtime_error(SDL_GetError());
    }
    if (Mix_AllocateChannels(16) != 16) {
        throw std::runtime_error(SDL_GetError());
    }
}

Audio::~Audio() {
    Mix_CloseAudio();
}

}
