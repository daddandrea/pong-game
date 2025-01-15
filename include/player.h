#pragma once

#include "character.h"
#include "input_manager.h"
#include <SDL2/SDL_keycode.h>

class Player : public Character, public InputManager {
public:
    void manage_key_down(SDL_Keycode key) override;
    void manage_key_up(SDL_Keycode key) override;
};
