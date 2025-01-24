#include "../include/character.h"
#include "../include/essentials.h"

#include <GL/gl.h>
#include <chrono>
#include <memory>
#include <stdexcept>

int Character::instances_count = 0;
bool Character::left_assigned = false;
bool Character::right_assigned = false;

std::ostream &operator<<(std::ostream &os, CharacterSide side) {
    switch (side) {
        case C_S_LEFT:
            os << "LEFT";
            break;
        case C_S_RIGHT:
            os << "RIGHT";
            break;
        default:
            os << "UNKNOWN";
            break;
    }
    return os;
}
std::ostream &operator<<(std::ostream &os,
                         CharacterVerticalMovementState state) {
    switch (state) {
        case C_V_M_STATIONARY:
            os << "STATIONARY";
            break;
        case C_V_M_MOVING_UP:
            os << "MOVING_UP";
            break;
        case C_V_M_MOVING_DOWN:
            os << "MOVING_DOWN";
            break;
        case C_V_M_STUCK_UP:
            os << "STUCK_UP";
            break;
        case C_V_M_STUCK_DOWN:
            os << "STUCK_DOWN";
            break;
        default:
            os << "UNKNOWN";
            break;
    }
    return os;
}

bool Character::is_parry_on_cooldown() const {
    auto current_time = std::chrono::steady_clock::now();
    std::chrono::duration<float> time_since_last_parry = current_time - last_parry_time;
    return time_since_last_parry.count() < PARRY_COOLDOWN_SECONDS;
}

bool Character::is_player() { return false; }
float Character::get_half_w() { return this->half_w; }
float Character::get_half_h() { return this->half_h; }
CharacterSide Character::get_side() { return this->side; }
CharacterSide Character::assign_side() {
    if (!left_assigned) {
        left_assigned = true;
        return C_S_LEFT;
    }
    if (!right_assigned) {
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
    this->ver_mov_state = state;
}
int Character::get_score() { return this->score;}
void Character::set_score(int score) { this->score = score; }
Color Character::get_color() { return this->color; }
void Character::set_color(Color color) { this->color = color; }
void Character::incr_speed() { this->speed_mult += CHARACTER_SPEED_INCR; }
void Character::draw_character() {
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_QUADS);
    glVertex3f(pos.x - CHARACTER_STANDARD_HALF_WIDTH,
               pos.y - CHARACTER_STANDARD_HALF_HEIGHT, 0.0);
    glVertex3f(pos.x + CHARACTER_STANDARD_HALF_WIDTH,
               pos.y - CHARACTER_STANDARD_HALF_HEIGHT, 0.0);
    glVertex3f(pos.x + CHARACTER_STANDARD_HALF_WIDTH,
               pos.y + CHARACTER_STANDARD_HALF_HEIGHT, 0.0);
    glVertex3f(pos.x - CHARACTER_STANDARD_HALF_WIDTH,
               pos.y + CHARACTER_STANDARD_HALF_HEIGHT, 0.0);
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
        case C_V_M_STUCK_UP:
            break;
        case C_V_M_STUCK_DOWN:
            break;
    }
}
void Character::update_collisions() {
    switch (this->collider->is_colliding_with_cage()) {
        case CAGE_SIDE_NONE:
        case CAGE_SIDE_LEFT:
        case CAGE_SIDE_RIGHT:
            break;
        case CAGE_SIDE_TOP:
            this->ver_mov_state = C_V_M_STUCK_UP;
            this->pos.y -= MARGIN;
            break;
        case CAGE_SIDE_BOTTOM:
            this->ver_mov_state = C_V_M_STUCK_DOWN;
            this->pos.y += MARGIN;
            break;
    }
}
void Character::render(float dt) {
    glPushMatrix();
    move_to_correct_side();
    draw_character();
    glPopMatrix();
    update_collisions();
    update_movement(dt);
    if (this->collider) {
        collider->set_position(this->pos);
    }
}

Character::Character()
    : half_w(CHARACTER_STANDARD_HALF_WIDTH),
    half_h(CHARACTER_STANDARD_HALF_HEIGHT), side(assign_side()),
    ver_mov_state(C_V_M_STATIONARY),
    last_parry_time(std::chrono::steady_clock::now()),
    can_parry(true),
    score(0),
    color(Color {0.0, 0.0, 0.0})
{
    this->collider = std::make_unique<RectangleCollider>(
        Vec2{pos.x, pos.y + (half_h / 2)}, CHARACTER_STANDARD_HALF_WIDTH,
        CHARACTER_STANDARD_HALF_HEIGHT);
}
Character::~Character() {
    instances_count--;
    if (side == C_S_LEFT)
        left_assigned = false;
    else
        right_assigned = false;
}
