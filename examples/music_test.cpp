#include <SDL_main.h>

#include <audio/audio.hpp>
#include <audio/chunk.hpp>
#include <audio/music.hpp>
#include <sdl/initialize.hpp>
#include <sdl/scene.hpp>

#include <examples/blib.wav.h>
#include <examples/test_music.mp3.h>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

class MusicTestScene : public engine::sdl::Scene {
public:
    MusicTestScene()
        : Scene(HEIGHT, window),
          window("visualizer",
                 SDL_WINDOWPOS_CENTERED,
                 SDL_WINDOWPOS_CENTERED,
                 WIDTH,
                 HEIGHT,
                 SDL_WINDOW_SHOWN),
          audio(44100, MIX_DEFAULT_FORMAT, 2, 128),
          music(test_music_mp3, sizeof(test_music_mp3)),
          chunk(blib_wav, sizeof(blib_wav)) {}

private:
    engine::sdl::OpenGlWindow window;
    engine::Audio audio;
    engine::Music music;
    engine::Chunk chunk;
    bool playing{false};

    void on_loop(float delta_time) override {}
    void on_key_pressed(SDL_Keycode code) override {
        switch (code) {
        case SDLK_SPACE:
            if (!playing) {
                music.fade_in(-1, 1000);
                playing = true;
            } else {
                engine::Music::fade_out(1000);
                playing = false;
            }
            break;
        case SDLK_RETURN:
            chunk.play(0);
            break;
        default:
            break;
        }
    }
};

int main(int argc, char *argv[]) {
#ifndef WIN32
    setenv("ALSA_CONFIG_DIR", "/usr/share/alsa", 1);
#endif
    engine::sdl::initialize init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    MusicTestScene scene;
    scene.run();
    return 0;
}
