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

    void exit();

private:
    bool fullscreen{false};
    int screen_height;
    OpenGlWindow &window;
    opengl::Screen *screen;
    bool finished{false};

    virtual void on_startup();
    virtual void on_shutdown();
    virtual void on_loop(float delta_time) = 0;
    virtual void on_key_pressed(SDL_Keycode code);
    virtual void on_mouse_button_down(int x, int y);
    virtual void on_mouse_button_up(int x, int y);
};

}
