#include "../include/game_object.h"

Vec2 GameObject::get_pos() {
    return this->pos;
}
void GameObject::set_pos(Vec2 pos) {
    this->pos = pos;
}
void GameObject::set_pos(float x, float y) {
    this->pos.x = x;
    this->pos.x = y;
}
Vec2 GameObject::get_speed() {
    return this->s;
}
void GameObject::set_speed(Vec2 s) {
    this->s = s;
}
void GameObject::set_speed(float x, float y) {
    this->s.x = x;
    this->s.y = y;
}
void GameObject::reset_speed() {
    this->s = Vec2 {GAME_OBJECT_STANDARD_SPEED_X, GAME_OBJECT_STANDARD_SPEED_Y};
}
float GameObject::get_speed_mult() {
    return this->speed_mult;
}
GameObject::GameObject() : pos(Vec2 {GAME_OBJECT_STANDARD_X, GAME_OBJECT_STANDARD_Y}), s(Vec2 {GAME_OBJECT_STANDARD_SPEED_X, GAME_OBJECT_STANDARD_SPEED_Y}), speed_mult(GAME_OBJECT_STANDARD_SPEED_MULTIPLIER) {}
GameObject::~GameObject() {}
