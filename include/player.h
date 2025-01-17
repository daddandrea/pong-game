#pragma once

#include "character.h"
#include "input_manager.h"

#include <chrono>
#include <SDL2/SDL_keycode.h>

#define PARRY_COOLDOWN_SECONDS 0.5f

class Player : public Character, public InputManager {
private:
    std::chrono::steady_clock::time_point last_parry_time;
    bool is_player_1;
    bool can_parry;
    bool is_parry_on_cooldown() const;
public:
    void manage_key_down_movement(SDL_Keycode key) override;
    void manage_key_down_actions(SDL_Keycode key, GameObject& other) override;
    void manage_key_up(SDL_Keycode key) override;
    Player();
};
