#include "../include/player.h"

void Player::manage_key_down(SDL_Keycode key) {
    // Movement
    if (key == SDLK_w) {
        this->ver_mov_state = C_V_M_MOVING_UP;
    } else if (key == SDLK_s) {
        this->ver_mov_state = C_V_M_MOVING_DOWN;
    }

    // Actions
}
void Player::manage_key_up(SDL_Keycode key) {
    // Movement
    if (key == SDLK_w) {
        this->ver_mov_state = C_V_M_STATIONARY;
    } else if (key == SDLK_s) {
        this->ver_mov_state = C_V_M_STATIONARY;
    }

    // Actions
}
