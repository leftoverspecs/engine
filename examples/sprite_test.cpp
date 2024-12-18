#include <SDL_main.h>

#include <opengl/spritemap.hpp>
#include <opengl/spriterenderer.hpp>

#include <sdl/initialize.hpp>
#include <sdl/openglwindow.hpp>
#include <sdl/scene.hpp>


#include <glm/gtc/matrix_transform.hpp>

#include <examples/test_sprite.png.h>

#ifdef _WIN32
extern "C" {

_declspec(dllexport) uint32_t NvOptimusEnablement = 0x00000001;
}
#endif

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

class SpriteTestScene : public engine::sdl::Scene {
public:
    SpriteTestScene()
        : Scene(HEIGHT, window), window("Sprite Test", SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        WIDTH,
                                        HEIGHT,
                                        SDL_WINDOW_SHOWN),
          sprites(test_sprite_png, sizeof(test_sprite_png), 1, 1),
          renderer(sprites, WIDTH, HEIGHT) {}


private:
    engine::sdl::OpenGlWindow window;
    engine::opengl::SpriteMap sprites;
    engine::opengl::SpriteRenderer renderer;

    void on_loop(float delta_time) override {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer.clear();
        glm::mat4 model(1.0f);
        int x, y;
        SDL_GetMouseState(&x, &y);
        model = translate(model, glm::vec3(x, HEIGHT - y, 0.0f));
        model = scale(model, glm::vec3(sprites.get_sprite_width(), sprites.get_sprite_height(), 1.0f));
        model = rotate(model, glm::radians(360.0f * static_cast<float>(SDL_GetTicks64()) / 1000.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = translate(model, glm::vec3(-0.5f, -0.5f, 0.0f));
        //model = glm::scale(model, glm::vec3(width - 20.0f, height - 20.0f, 1.0f));
        renderer.queue(model, glm::vec4(1.0, 1.0f, 1.0f, 1.0f), 0, 0);
        renderer.draw();

    }
};


int main(int argc, char *argv[]) {
    engine::sdl::initialize init(SDL_INIT_VIDEO);
    SpriteTestScene scene;
    scene.run();
    return 0;
}
