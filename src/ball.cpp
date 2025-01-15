#include "../include/ball.h"
#include <GL/gl.h>
#include <cmath>
#include <memory>

#define BALL_STANDARD_COLOR 1.0, 0.0, 0.0

std::ostream& operator<<(std::ostream& os, BallHorizontalMovementState state) {
    switch (state) {
        case B_H_M_STATIONARY: os << "STATIONARY"; break;
        case B_H_M_LEFT: os << "LEFT"; break;
        case B_H_M_RIGHT: os << "RIGHT"; break;
        default: os << "UNKNOWN"; break;
    }
    return os;
}
std::ostream& operator<<(std::ostream& os, BallVerticalMovementState state) {
    switch (state) {
        case B_V_M_STATIONARY: os << "STATIONARY"; break;
        case B_V_M_DOWN: os << "DOWN"; break;
        case B_V_M_UP: os << "UP"; break;
        default: os << "UNKNOWN"; break;
    }
    return os;
}

void Ball::draw_debug_info() {

}

float Ball::get_radius() {
    return this->r;
}
BallHorizontalMovementState Ball::get_hor_mov_state() {
    return this->hor_mov_state;
}
void Ball::set_hor_mov_state(BallHorizontalMovementState state) {
    this->hor_mov_state = state;
}
BallVerticalMovementState Ball::get_ver_mov_state() {
    return this->ver_mov_state;
}
void Ball::set_ver_mov_state(BallVerticalMovementState state) {
    this->ver_mov_state = state;
}
void Ball::incr_speed() {
    this->speed_mult += BALL_SPEED_INCR;
}
void Ball::draw_ball() {
    glColor3f(BALL_STANDARD_COLOR);
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(this->pos.x, this->pos.y, 0.0);
        for (int i = 0; i <= 360; i += 10) {
        float theta = i * M_PI / 180.0;
        glVertex3f(
            this->pos.x + BALL_RADIUS * cos(theta),
            this->pos.y + BALL_RADIUS * sin(theta),
            0.0);
    }
    glEnd();
}
void Ball::update_movement(float dt) {
    if (this->hor_mov_state == B_H_M_STATIONARY && this->ver_mov_state == B_V_M_STATIONARY) {
        this->reset_speed();
        this->set_pos(Vec2 {BALL_DEFAULT_X, BALL_DEFAULT_Y});
    }

    if (this->hor_mov_state == B_H_M_LEFT)
        this->pos.x -= this->s.x * this->speed_mult * dt;
    else if (this->hor_mov_state == B_H_M_RIGHT)
        this->pos.y += this->s.x * this->speed_mult * dt;

    if (this->ver_mov_state == B_V_M_DOWN)
        this->pos.y -= this->s.y * this->speed_mult * dt;
    else if (this->ver_mov_state == B_V_M_UP)
        this->pos.y += this->s.y * this->speed_mult * dt;
}
void Ball::render(float dt) {
    glPushMatrix();
    //glTranslatef(this->pos.x, this->pos.y, 0.0);
    draw_ball();
    draw_debug_info();
    glPopMatrix();
    update_movement(dt);
    if (this->collider) {
        this->collider->set_position(this->pos);
    }
}
Ball::Ball() : r(BALL_RADIUS), hor_mov_state(B_H_M_STATIONARY), ver_mov_state(B_V_M_STATIONARY) {
    this->collider = std::make_unique<CircleCollider>(
        pos,
        BALL_RADIUS
    );
}
