#include "../include/game_object.h"

std::unique_ptr<Collider>& GameObject::get_collider() {
    return this->collider;
}
Vec2 GameObject::get_pos() {
    return this->pos;
}
void GameObject::set_pos(Vec2 pos) {
    this->pos = pos;
}
Vec2 GameObject::get_speed() {
    return this->s;
}
void GameObject::set_speed(Vec2 s) {
    this->s = s;
}
void GameObject::reset_pos() {
    this->pos = Vec2 {GAME_OBJECT_STANDARD_X, GAME_OBJECT_STANDARD_Y};
}
void GameObject::reset_speed_incr() {
    this->speed_mult = GAME_OBJECT_STANDARD_SPEED_MULTIPLIER;
}
float GameObject::get_speed_mult() {
    return this->speed_mult;
}

GameObject::GameObject() : pos(Vec2 {GAME_OBJECT_STANDARD_X, GAME_OBJECT_STANDARD_Y}), s(Vec2 {GAME_OBJECT_STANDARD_SPEED_X, GAME_OBJECT_STANDARD_SPEED_Y}), speed_mult(GAME_OBJECT_STANDARD_SPEED_MULTIPLIER) {}
GameObject::~GameObject() {}
