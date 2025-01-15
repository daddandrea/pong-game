#pragma once

#include "essentials.h"

class Collider {
public:
    virtual bool is_colliding(const Collider& other) const = 0;
    virtual void set_position(Vec2 pos) = 0;
    virtual ~Collider() = default;
};

class RectangleCollider : public Collider {
private:
    Vec2 position;
    float half_width;
    float half_height;
public:
    bool is_colliding(const Collider& other) const override;
    Vec2 get_position() const;
    void set_position(Vec2 pos) override;
    float get_half_width() const;
    float get_half_height() const;
    RectangleCollider(Vec2 pos, float half_w, float half_h);
};

class CircleCollider : public Collider {
private:
    Vec2 position;
    float radius;

public:
    bool is_colliding(const Collider& other) const override;
    Vec2 get_position() const;
    void set_position(Vec2 pos) override;
    float get_radius() const;
    CircleCollider(Vec2 pos, float r);
};
