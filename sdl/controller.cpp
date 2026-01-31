#include "controller.hpp"

namespace engine::sdl {

Controller::Controller(int id)
  : controller(SDL_GameControllerOpen(id)),
    axis{},
    buttons{}
{
    if (controller == nullptr) {
        keyboard.emplace();
    } else {
        SDL_AddEventWatch(event_filter, this);
    }
}

Controller::~Controller() {
    if (!keyboard) {
        SDL_DelEventWatch(event_filter, this);
        SDL_GameControllerClose(controller);
    }
}

int Controller::is_button_a_pressed() const {
    if (!keyboard) {
        return buttons[SDL_CONTROLLER_BUTTON_A];
    }
    return keyboard->is_space_pressed();
}

int Controller::is_button_b_pressed() const {
    if (!keyboard) {
        return buttons[SDL_CONTROLLER_BUTTON_B];
    }
    return keyboard->is_space_pressed();
}

int Controller::is_button_x_pressed() const {
    if (!keyboard) {
        return buttons[SDL_CONTROLLER_BUTTON_X];
    }
    return keyboard->is_space_pressed();
}

int Controller::is_button_y_pressed() const {
    if (!keyboard) {
        return buttons[SDL_CONTROLLER_BUTTON_Y];
    }
    return keyboard->is_space_pressed();
}

int Controller::is_button_up_pressed() const {
    if (!keyboard) {
        return buttons[SDL_CONTROLLER_BUTTON_DPAD_UP];
    }
    return keyboard->is_up_pressed();
}

int Controller::is_button_down_pressed() const {
    if (!keyboard) {
        return buttons[SDL_CONTROLLER_BUTTON_DPAD_DOWN];
    }
    return keyboard->is_down_pressed();
}

int Controller::is_button_left_pressed() const {
    if (!keyboard) {
        return buttons[SDL_CONTROLLER_BUTTON_DPAD_LEFT];
    }
    return keyboard->is_left_pressed();
}

int Controller::is_button_right_pressed() const {
    if (!keyboard) {
        return buttons[SDL_CONTROLLER_BUTTON_DPAD_RIGHT];
    }
    return keyboard->is_right_pressed();
}

int Controller::get_right_trigger() const {
    if (!keyboard) {
        return axis[SDL_CONTROLLER_AXIS_TRIGGERRIGHT] + buttons[SDL_CONTROLLER_BUTTON_RIGHTSHOULDER];
    }
    return keyboard->is_lshift_pressed();
}

glm::vec2 Controller::get_joystick_position() const {
    const int x = axis[SDL_CONTROLLER_AXIS_LEFTX];
    const int y = axis[SDL_CONTROLLER_AXIS_LEFTY];
    const float fx = x < 0 ? static_cast<float>(x) / static_cast<float>(-SDL_JOYSTICK_AXIS_MIN) : static_cast<float>(x) / static_cast<float>(SDL_JOYSTICK_AXIS_MAX);
    const float fy = y < 0 ? static_cast<float>(y) / static_cast<float>(-SDL_JOYSTICK_AXIS_MIN) : static_cast<float>(y) / static_cast<float>(SDL_JOYSTICK_AXIS_MAX);
    return {fx, fy};
}

void Controller::rumble(Uint16 low_freq, Uint16 high_freq, Uint32 duration) const {
    if (!keyboard) {
        SDL_GameControllerRumble(controller, low_freq, high_freq, duration);
    }
}

void Controller::reset() {
    axis = { 0 };
    buttons = { 0 };
}

int Controller::get_num_controllers() {
    return SDL_NumJoysticks();
}

int Controller::filter_events(const SDL_Event *event) {
    switch (event->type) {
        case SDL_CONTROLLERAXISMOTION: {
            const SDL_ControllerAxisEvent a = event->caxis;
            if (SDL_GameControllerFromInstanceID(a.which) == controller) {
                axis[a.axis] = a.value;
            }
            break;
        }
        case SDL_CONTROLLERBUTTONDOWN:
        case SDL_CONTROLLERBUTTONUP: {
            const SDL_ControllerButtonEvent b = event->cbutton;
            if (SDL_GameControllerFromInstanceID(b.which) == controller) {
                if (b.state == SDL_PRESSED) {
                    ++buttons[b.button];
                } else if (b.state == SDL_RELEASED) {
                    buttons[b.button] = 0;
                }
            }
            break;
        }
        default:
            break;
    }
    return 0;
}

int Controller::event_filter(void *userdata, SDL_Event *event) {
    Controller *const self = static_cast<Controller *>(userdata);
    return self->filter_events(event);
}

}
