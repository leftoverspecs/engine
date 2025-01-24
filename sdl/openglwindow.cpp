#include "openglwindow.hpp"

#include <GL/glew.h>

#include <stdexcept>

namespace engine::sdl {

OpenGlWindow::OpenGlAttributes::OpenGlAttributes() {
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
}

OpenGlWindow::OpenGlWindow(const char *title,
                           int x, int y, int w,
                           int h, Uint32 flags)
    : window{title, x, y, w, h, flags | SDL_WINDOW_OPENGL},
      context{SDL_GL_CreateContext(window.get_window())} {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("Failed to initialize GLEW");
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glViewport(0, 0, w, h);
}

OpenGlWindow::~OpenGlWindow() {
    SDL_GL_DeleteContext(context);
}

void OpenGlWindow::swap_window() const {
    SDL_GL_SwapWindow(window.get_window());
}

void OpenGlWindow::set_title(const char *title) const {
    window.set_title(title);
}

}// namespace engine::sdl
