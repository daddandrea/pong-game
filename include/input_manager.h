#pragma once

#include <SDL2/SDL_keycode.h>

class InputManager {
public:
    virtual void manage_key_down(SDL_Keycode key) = 0;
    virtual void manage_key_up(SDL_Keycode key) = 0;
};
