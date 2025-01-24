#pragma once

#include "character.h"

class Ball;

class Cpu : public Character {
private:
    Ball& ball_ref;
    bool can_parry;
    void decide_movement();
    void decide_actions();
public:
    void render(float dt) override;
    Cpu(Ball& ball_ref, bool can_parry);
};
