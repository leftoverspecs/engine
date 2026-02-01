#pragma once

#include "opengl/screen.hpp"
#include "openglwindow.hpp"


#include <opengl/destination.hpp>

#include <SDL.h>

namespace engine::sdl {

class Scene {
public:
    explicit Scene(opengl::Screen &screen, int screen_height, OpenGlWindow &window);
    virtual ~Scene() = default;

    bool run();
    bool fade_in_and_run(float time);

    void exit();
    void fade_out(float time);

    bool is_fading_out() const { return fade_out_timer > 0.0f; }
    bool is_fullscreen() const { return fullscreen; }
    void set_fullscreen(bool value);

private:
    bool fullscreen{false};
    int screen_height;
    OpenGlWindow &window;
    opengl::Screen *screen;

    float fade_in_timer{-1.0f};
    float current_fade_in_timer{-1.0f};

    float fade_out_timer{-1.0f};
    float current_fade_out_timer{-1.0f};
    bool finished{false};

    virtual void on_startup();
    virtual void on_shutdown();
    virtual void on_faded_in();
    virtual void on_loop(float delta_time) = 0;
    virtual void on_key_pressed(SDL_Keycode code);
    virtual void on_mouse_button_down(int x, int y);
    virtual void on_mouse_button_up(int x, int y);
};

}
