#pragma once

#include "game_object.h"
#include <ostream>

#define BALL_DEFAULT_X 0.0f
#define BALL_DEFAULT_Y 0.0f
#define BALL_RADIUS 0.3f
#define BALL_SPEED_INCR 0.1f

enum BallHorizontalMovementState { B_H_M_STATIONARY, B_H_M_LEFT, B_H_M_RIGHT };
std::ostream& operator<<(std::ostream& os, BallHorizontalMovementState state);

enum BallVerticalMovementState { B_V_M_STATIONARY, B_V_M_DOWN, B_V_M_UP };
std::ostream& operator<<(std::ostream& os, BallVerticalMovementState state);

class Ball : public GameObject {
private:
    float r;
    BallHorizontalMovementState hor_mov_state;
    BallVerticalMovementState ver_mov_state;
    void draw_ball();
    void update_movement(float dt) override;
public:
    void draw_debug_info() override;
    float get_radius();
    BallHorizontalMovementState get_hor_mov_state();
    void set_hor_mov_state(BallHorizontalMovementState state);
    BallVerticalMovementState get_ver_mov_state();
    void set_ver_mov_state(BallVerticalMovementState state);
    void incr_speed() override;
    void render(float dt) override;
    Ball();
    ~Ball() = default;
};

