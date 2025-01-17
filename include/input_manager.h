#pragma once

#include "game_object.h"
#include <SDL2/SDL_keycode.h>

class InputManager {
public:
    virtual void manage_key_down_movement(SDL_Keycode key) = 0;
    virtual void manage_key_down_actions(SDL_Keycode key, GameObject& other) = 0;
    virtual void manage_key_up(SDL_Keycode key) = 0;
};
