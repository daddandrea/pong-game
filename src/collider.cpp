#include "../include/collider.h"
#include "../include/game.h"
#include <algorithm>
#include <cstdlib>

bool RectangleCollider::is_colliding(const Collider& other) const {
    return check_collision_with_margin(other, 0.0f);
}
CageSide RectangleCollider::is_colliding_with_cage() const {
    if (position.y - half_height <= -(CAGE_HALF_HEIGHT - MARGIN)) {
        return CAGE_SIDE_BOTTOM;
    } else if (position.y + half_height >= CAGE_HALF_HEIGHT - MARGIN) {
        return CAGE_SIDE_TOP;
    } else {
        return CAGE_SIDE_NONE;
    }
}
bool RectangleCollider::is_in_parry_range(const Collider& other) const {
    return check_collision_with_margin(other, COLLIDER_COYOTE_MARGIN);
}

bool RectangleCollider::check_collision_with_margin(const Collider& other, float margin) const {
    if (const RectangleCollider* rect = dynamic_cast<const RectangleCollider*>(&other)) {
        float dx = std::abs(position.x - rect->get_position().x);
        float dy = std::abs(position.y - rect->get_position().y);

        return dx < (half_width + rect->get_half_width() + margin) && dy < (half_height + rect->get_half_height() + margin);
    }
    if (const CircleCollider* circle = dynamic_cast<const CircleCollider*>(&other)) {
        float closest_x = std::max(position.x - half_width - margin, 
                         std::min(circle->get_position().x, position.x + half_width + margin));
        float closest_y = std::max(position.y - half_height - margin,
                         std::min(circle->get_position().y, position.y + half_height+ margin));
        float dx = closest_x - circle->get_position().x;
        float dy = closest_y - circle->get_position().y;
        float distance_squared = dx * dx + dy * dy;
        return distance_squared <= ((circle->get_radius() + margin) * (circle->get_radius() + margin));
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
    return check_collision_with_margin(other, 0.0f);
}
CageSide CircleCollider::is_colliding_with_cage() const {
    if (position.x - radius <= -CAGE_HALF_WIDTH)
        return CAGE_SIDE_LEFT;
    else if (position.x + radius >= CAGE_HALF_WIDTH)
        return CAGE_SIDE_RIGHT;
    else if (position.y - radius <= -CAGE_HALF_HEIGHT)
        return CAGE_SIDE_BOTTOM;
    else if (position.y + radius >= CAGE_HALF_HEIGHT)
        return CAGE_SIDE_TOP;
    else
        return CAGE_SIDE_NONE;
}
bool CircleCollider::is_in_parry_range(const Collider& other) const {
    return check_collision_with_margin(other, COLLIDER_COYOTE_MARGIN);
}
bool CircleCollider::check_collision_with_margin(const Collider& other, float margin) const {
    if (const CircleCollider* circle = dynamic_cast<const CircleCollider*>(&other)) {
        float dx = position.x - circle->get_position().x;
        float dy = position.y - circle->get_position().y;
        float distance_squared = dx * dx + dy * dy;
        float combined_radius = radius + circle->get_radius() + margin;
        return distance_squared <= (combined_radius * combined_radius);
    }
    if (const RectangleCollider* rect = dynamic_cast<const RectangleCollider*>(&other)) {
        return rect->check_collision_with_margin(*this, margin);
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
