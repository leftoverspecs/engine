#include "sdl/initialize.hpp"


#include <sdl/scene.hpp>


#include <fstream>
#include <opengl/model.h>
#include <sdl/openglwindow.hpp>
#include <vector>

#include <examples/cube.mod.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

class ModelTestScene : public engine::sdl::Scene {
public:
    ModelTestScene()
        : Scene(screen, HEIGHT, window),
          window("Sprite Test", SDL_WINDOWPOS_CENTERED,
                 SDL_WINDOWPOS_CENTERED,
                 WIDTH,
                 HEIGHT,
                 SDL_WINDOW_SHOWN),
          screen(WIDTH, HEIGHT),
          model(reinterpret_cast<const char *>(cube_mod), sizeof(cube_mod)) {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glDepthMask(GL_TRUE);
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
    }

private:
    engine::sdl::OpenGlWindow window;
    engine::opengl::Screen screen;
    engine::opengl::Model model;

    void on_loop(float delta_time) override {
        int x, y;
        SDL_GetMouseState(&x, &y);
        const float u = 2.0f * static_cast<float>(x) / WIDTH - 1.0f;
        const float v = -(2.0f * static_cast<float>(y) / HEIGHT - 1.0f);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));

        const glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(WIDTH) / HEIGHT, 0.1f, 200.0f);

        glm::mat4 m(1.0f);
        m = glm::rotate(m, glm::radians(-90.0f * v), glm::vec3(1.0f, 0.0f, 0.0f));
        m = glm::rotate(m, glm::radians(180.0f * u), glm::vec3(0.0f, 1.0f, 0.0f));

        model.draw(glm::vec3(0.0f, 0.0f, 2.0f),
            glm::vec3(1.0f, 1.0f, 0.0f),
            projection,
            view,
            m,
            glm::vec3(1.0f, 1.0, 1.0f));
    }
};

int main() {
    engine::sdl::initialize init(SDL_INIT_VIDEO);
    ModelTestScene model;
    model.run();
    return 0;
}
