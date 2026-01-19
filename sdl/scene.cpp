#include "scene.hpp"

#include <SDL.h>

namespace engine::sdl {

Scene::Scene(opengl::Screen &screen, int screen_height, OpenGlWindow &window)
    : screen(&screen), screen_height{screen_height}, window{window} {}

bool Scene::run() {
    return fade_in_and_run(0.0f);
}

bool Scene::fade_in_and_run(float time) {
    if (time > 0.0f) {
        fade_in_timer = time;
        current_fade_in_timer = 0.0f;
    }
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
        GLfloat value = 1.0f;
        if (fade_in_timer > 0.0f) {
            current_fade_in_timer += delta_time;
            value = current_fade_in_timer / fade_in_timer;
            if (current_fade_in_timer > fade_in_timer) {
                current_fade_in_timer = -1.0f;
                fade_in_timer = -1.0f;
                value = 1.0f;
                on_faded_in();
            }
        }
        if (fade_out_timer > 0.0f) {
            current_fade_out_timer += delta_time;
            value = 1.0f - current_fade_out_timer / fade_out_timer;
            if (current_fade_out_timer >= fade_out_timer) {
                finished = true;
                fade_out_timer = -1.0f;
                current_fade_out_timer = -1.0f;
                value = 0.0f;
            }
        }
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        screen->draw(glm::vec4(value, value, value, 1.0f));
        window.swap_window();
    }
    on_shutdown();
    return true;
}

void Scene::exit() {
    finished = true;
}

void Scene::fade_out(float time) {
    fade_out_timer = time;
    current_fade_out_timer = 0.0f;
}

void Scene::on_startup() {}
void Scene::on_shutdown() {}
void Scene::on_faded_in() {}

void Scene::on_key_pressed(SDL_Keycode code) {}
void Scene::on_mouse_button_down(int x, int y) {}
void Scene::on_mouse_button_up(int x, int y) {}

}
