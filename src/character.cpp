#include "../include/character.h"
#include "../include/essentials.h"

#include <GL/gl.h>
#include <memory>
#include <stdexcept>

#define CHARACTER_STANDARD_COLOR 0.0, 1.0, 0.0

int Character::instances_count = 0;
bool Character::left_assigned = false;
bool Character::right_assigned = false;

std::ostream& operator<<(std::ostream& os, CharacterSide side) {
    switch (side) {
        case C_S_LEFT: os << "LEFT"; break;
        case C_S_RIGHT: os << "RIGHT"; break;
        default: os << "UNKNOWN"; break;
    }
    return os;
}
std::ostream& operator<<(std::ostream& os, CharacterVerticalMovementState state) {
    switch (state) {
        case C_V_M_STATIONARY: os << "STATIONARY"; break;
        case C_V_M_MOVING_UP: os << "MOVING_UP"; break;
        case C_V_M_MOVING_DOWN: os << "MOVING_DOWN"; break;
        default: os << "UNKNOWN"; break;
    }
    return os;
}

void Character::draw_debug_info() {

}

float Character::get_half_w() {
    return this->half_w;
}
float Character::get_half_h() {
    return this->half_h;
}
CharacterSide Character::get_side() {
    return this->side;
}
CharacterSide Character::assign_side() {
    if (!left_assigned) {
        left_assigned = true;
        return C_S_LEFT;
    } if (!right_assigned) {
        right_assigned = true;
        return C_S_RIGHT;
    } else {
        throw std::runtime_error("Both sides are already assigned!");
    }
}
void Character::move_to_correct_side() {
    switch (this->side) {
        case C_S_LEFT:
            this->pos.x = CHARACTER_LEFT_STANDARD_X;
            break;
        case C_S_RIGHT:
            this->pos.x = CHARACTER_RIGHT_STANDARD_X;
            break;
        default:
            throw std::runtime_error("Illegal side value.");
            break;
    }
}
CharacterVerticalMovementState Character::get_ver_mov_state() {
    return this->ver_mov_state;
}
void Character::set_ver_mov_state(CharacterVerticalMovementState state) {
    this->set_ver_mov_state(state);
}
void Character::incr_speed() {
    this->speed_mult += CHARACTER_SPEED_INCR;
}
void Character::draw_character() {
    glColor3f(CHARACTER_STANDARD_COLOR);
    glBegin(GL_QUADS);
        //glVertex3f(-this->pos.x,-this->pos.y, 0.0);
        //glVertex3f( this->pos.x,-this->pos.y, 0.0);
        //glVertex3f( this->pos.x, this->pos.y, 0.0);
        //glVertex3f(-this->pos.x, this->pos.y, 0.0);
        glVertex3f(this->pos.x - CHARACTER_STANDARD_HALF_WIDTH, this->pos.y - CHARACTER_STANDARD_HALF_HEIGHT, 0.0);
        glVertex3f(this->pos.x + CHARACTER_STANDARD_HALF_WIDTH, this->pos.y - CHARACTER_STANDARD_HALF_HEIGHT, 0.0);
        glVertex3f(this->pos.x + CHARACTER_STANDARD_HALF_WIDTH, this->pos.y + CHARACTER_STANDARD_HALF_HEIGHT, 0.0);
        glVertex3f(this->pos.x - CHARACTER_STANDARD_HALF_WIDTH, this->pos.y + CHARACTER_STANDARD_HALF_HEIGHT, 0.0);
    glEnd();
}
void Character::update_movement(float dt) {
    switch (this->ver_mov_state) {
        case C_V_M_STATIONARY:
            // reset_speed();
            break;
        case C_V_M_MOVING_UP:
            this->pos.y += this->s.y * this->speed_mult * dt;
            break;
        case C_V_M_MOVING_DOWN:
            this->pos.y -= this->s.y * this->speed_mult * dt;
            break;
    }
}
void Character::render(float dt) {
    glPushMatrix();
    switch (this->side) {
        case C_S_LEFT:
            glTranslatef(CHARACTER_LEFT_STANDARD_X, this->pos.y, 0.0);
            break;
        case C_S_RIGHT:
            glTranslatef(CHARACTER_RIGHT_STANDARD_X, this->pos.y, 0.0);
            break;
        default:
            throw std::runtime_error("Illegal side value.");
            break;
    }
    draw_character();
    draw_debug_info();
    glPopMatrix();
    update_movement(dt);
    if (this->collider) {
        collider->set_position(this->pos);
    }
}

Character::Character() : half_w(CHARACTER_STANDARD_HALF_WIDTH), half_h(CHARACTER_STANDARD_HALF_HEIGHT), side(assign_side()), ver_mov_state(C_V_M_STATIONARY) {
    this->collider = std::make_unique<RectangleCollider>(
        pos,
        CHARACTER_STANDARD_HALF_WIDTH,
        CHARACTER_STANDARD_HALF_HEIGHT
    );
}
