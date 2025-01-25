#include "keyboard.hpp"

namespace engine::sdl {

Keyboard::Keyboard() {
    SDL_AddEventWatch(event_filter, this);
}

Keyboard::~Keyboard() {
    SDL_DelEventWatch(event_filter, this);
}

int Keyboard::filter_events(const SDL_Event *event) {
    switch (event->type) {
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym) {
        case SDLK_LEFT:
            ++left;
            break;
        case SDLK_RIGHT:
            ++right;
            break;
        case SDLK_SPACE:
            ++space;
            break;
        case SDLK_a:
            ++a;
            break;
        case SDLK_d:
            ++d;
            break;
        case SDLK_LSHIFT:
            ++lshift;
            break;
        default:
            break;
        }
        break;
    case SDL_KEYUP:
        switch (event->key.keysym.sym) {
        case SDLK_LEFT:
            left = 0;
            break;
        case SDLK_RIGHT:
            right = 0;
            break;
        case SDLK_SPACE:
            space = 0;
            break;
        case SDLK_a:
            a = 0;
            break;
        case SDLK_d:
            d = 0;
            break;
        case SDLK_LSHIFT:
            lshift = 0;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    return 0;
}

int Keyboard::event_filter(void *userdata, SDL_Event *event) {
    Keyboard *const self = static_cast<Keyboard *>(userdata);
    return self->filter_events(event);
}

}
