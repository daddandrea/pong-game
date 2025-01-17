#include "../include/player.h"
#include "../include/ball.h"
#include <SDL2/SDL_keycode.h>
#include <cstdlib>
#include <stdexcept>

void Player::manage_key_down_movement(SDL_Keycode key) {
    if (key == SDLK_w && this->ver_mov_state != C_V_M_STUCK_UP) {
        this->ver_mov_state = C_V_M_MOVING_UP;
    } else if (key == SDLK_s && this->ver_mov_state != C_V_M_STUCK_DOWN) {
        this->ver_mov_state = C_V_M_MOVING_DOWN;
    }
}
void Player::manage_key_down_actions(SDL_Keycode key, GameObject& other) {
    Ball* ball = dynamic_cast<Ball*>(&other);

    if (!ball) {
        throw std::runtime_error("The GameObject provided isn't a Ball.");
    }

    if (key == SDLK_SPACE) {
        bool is_ball_stationary = ball->get_hor_mov_state() == B_H_M_STATIONARY && ball->get_ver_mov_state() == B_V_M_STATIONARY;
        bool is_in_parry_range = this->collider->is_in_parry_range(*ball->get_collider());

        if (is_ball_stationary) {
            ball->set_hor_mov_state(rand() % 2 == 0 ? B_H_M_LEFT : B_H_M_RIGHT);
            ball->set_ver_mov_state(rand() % 2 == 0 ? B_V_M_UP : B_V_M_DOWN);
            ball->set_speed(Vec2 {GAME_OBJECT_STANDARD_SPEED_X, GAME_OBJECT_STANDARD_SPEED_Y});
        } else if (is_in_parry_range) {
            if (ball->get_hor_mov_state() == B_H_M_LEFT)
                ball->set_hor_mov_state(B_H_M_RIGHT);
            else
                ball->set_hor_mov_state(B_H_M_LEFT);

            if (this->get_ver_mov_state() == C_V_M_MOVING_UP)
                ball->set_ver_mov_state(B_V_M_UP);
            else if (this->get_ver_mov_state() == C_V_M_MOVING_DOWN)
                ball->set_ver_mov_state(B_V_M_DOWN);
            ball->incr_speed();
        }
    }
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
