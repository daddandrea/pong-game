#pragma once

#include "collider.h"
#include "debugger.h"
#include "essentials.h"
#include "mover.h"
#include <memory>

#define GAME_OBJECT_INITIAL_SPEED_X 0.0
#define GAME_OBJECT_INITIAL_SPEED_Y 0.0
#define GAME_OBJECT_STANDARD_SPEED_X 5.0
#define GAME_OBJECT_STANDARD_SPEED_Y 5.0
#define GAME_OBJECT_STANDARD_SPEED_MULTIPLIER 1.0
#define GAME_OBJECT_STANDARD_X 0.0
#define GAME_OBJECT_STANDARD_Y 0.0

class GameObject : public Mover {
protected:
  std::unique_ptr<Collider> collider;
  Vec2 pos;
  Vec2 s;
  float speed_mult;

public:
  std::unique_ptr<Collider> &get_collider();
  Vec2 get_pos();
  void set_pos(Vec2 pos);
  Vec2 get_speed();
  void set_speed(Vec2 s);
  void reset_pos();
  void reset_speed_incr();
  float get_speed_mult();
  virtual void incr_speed() = 0;
  virtual void render(float dt) = 0;
  GameObject();
  virtual ~GameObject();
};
