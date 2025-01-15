#include "../include/collider.h"
#include <algorithm>
#include <cstdlib>

bool RectangleCollider::is_colliding(const Collider& other) const {
    if (const RectangleCollider* rect = dynamic_cast<const RectangleCollider*>(&other)) {
        float dx = std::abs(position.x - rect->get_position().x);
        float dy = std::abs(position.y - rect->get_position().y);

        return dx < (half_width + rect->get_half_width()) && dy < (half_height + rect->get_half_height());
    }
    if (const CircleCollider* circle = dynamic_cast<const CircleCollider*>(&other)) {
        float closest_x = std::max(position.x - half_width, 
                         std::min(circle->get_position().x, position.x + half_width));
        float closest_y = std::max(position.y - half_height,
                         std::min(circle->get_position().y, position.y + half_height));
        float dx = closest_x - circle->get_position().x;
        float dy = closest_y - circle->get_position().y;
        float distance_squared = dx * dx + dy * dy;
        return distance_squared <= (circle->get_radius() * circle->get_radius());
    }

    return false;
}
Vec2 RectangleCollider::get_position() const {
    return this->position;
}
void RectangleCollider::set_position(Vec2 pos) {
    this->position.x = pos.x;
    this->position.y = pos.y;
}
float RectangleCollider::get_half_width() const {
    return this->half_width;
}
float RectangleCollider::get_half_height() const {
    return this->half_height;
}
RectangleCollider::RectangleCollider(Vec2 pos, float half_w, float half_h) : position(pos), half_width(half_w), half_height(half_h) {}

bool CircleCollider::is_colliding(const Collider& other) const {
    if (const CircleCollider* circle = dynamic_cast<const CircleCollider*>(&other)) {
        float dx = position.x - circle->get_position().x;
        float dy = position.y - circle->get_position().y;
        float distance_squared = dx * dx + dy * dy;
        float combined_radius = radius + circle->get_radius();
        return distance_squared <= (combined_radius * combined_radius);
    }
    if (const RectangleCollider* rect = dynamic_cast<const RectangleCollider*>(&other)) {
        return rect->is_colliding(*this);
    }
    return false;
}
Vec2 CircleCollider::get_position() const {
    return position;
}
void CircleCollider::set_position(Vec2 pos) {
    position = pos;
}
float CircleCollider::get_radius() const {
    return radius;
}
CircleCollider::CircleCollider(Vec2 pos, float r) : position(pos), radius(r) {}
