#include "scene.hpp"

#include <SDL.h>

namespace engine::sdl {

Scene::Scene(opengl::Screen &screen, int screen_height, OpenGlWindow &window)
    : screen(&screen), screen_height{screen_height}, window{window} {}

bool Scene::run() {
    on_startup();
    finished = false;
    Uint64 last = SDL_GetTicks64();
    while (!finished) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                return false;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    return false;
                case SDLK_f:
                    fullscreen = !fullscreen;
                    window.set_fullscreen(fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
                    screen->switch_fullscreen(window.get_window_display_index(), fullscreen);
                    break;
                default:
                    on_key_pressed(event.key.keysym.sym);
                    break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    on_mouse_button_up(event.button.x, screen_height - event.button.y);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    on_mouse_button_down(event.button.x, screen_height - event.button.y);
                }
                break;
            default:
                break;
            }
        }

        const Uint64 next = SDL_GetTicks64();
        const auto delta_time = static_cast<float>(next - last);
        last = next;
        {
            auto binding = screen->bind_as_target();
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            on_loop(delta_time);
        }
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        screen->draw(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        window.swap_window();
        window.set_title(std::to_string(1000.0 / delta_time).c_str());
    }
    on_shutdown();
    return true;
}

void Scene::exit() {
    finished = true;
}

void Scene::on_startup() {}
void Scene::on_shutdown() {}

void Scene::on_key_pressed(SDL_Keycode code) {}
void Scene::on_mouse_button_down(int x, int y) {}
void Scene::on_mouse_button_up(int x, int y) {}

}
