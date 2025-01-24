#pragma once

#include "game_object.h"
#include "essentials.h"
#include "mover.h"
#include <ostream>
#include <chrono>

#define CHARACTER_RIGHT_STANDARD_X (get_cage_half_w() - MARGIN - CHARACTER_STANDARD_HALF_WIDTH)
#define CHARACTER_LEFT_STANDARD_X -CHARACTER_RIGHT_STANDARD_X
#define CHARACTER_STANDARD_Y 0.0
#define CHARACTER_STANDARD_HALF_WIDTH 0.3f
#define CHARACTER_STANDARD_HALF_HEIGHT 1.1f
#define CHARACTER_SPEED_INCR 0.1f
#define PARRY_COOLDOWN_SECONDS 0.5f

enum CharacterSide { C_S_LEFT, C_S_RIGHT };
std::ostream& operator<<(std::ostream& os, CharacterSide side);

enum CharacterVerticalMovementState { C_V_M_STATIONARY, C_V_M_MOVING_UP, C_V_M_MOVING_DOWN, C_V_M_STUCK_UP, C_V_M_STUCK_DOWN };
std::ostream& operator<<(std::ostream& os, CharacterVerticalMovementState state);

class Character : public GameObject {
protected:
    static int instances_count;
    static bool left_assigned;
    static bool right_assigned;
    float half_w;
    float half_h;
    CharacterSide side;
    CharacterVerticalMovementState ver_mov_state;
    std::chrono::steady_clock::time_point last_parry_time;
    bool is_player_1;
    bool can_parry;
    int score;
    Color color;
    bool is_parry_on_cooldown() const;
    void draw_character();
    void update_movement(float dt) override;
    void update_collisions();
    CharacterSide assign_side();
    void move_to_correct_side();
public:
    virtual bool is_player();
    float get_half_w();
    float get_half_h();
    CharacterSide get_side();
    CharacterVerticalMovementState get_ver_mov_state();
    void set_ver_mov_state(CharacterVerticalMovementState state);
    int get_score();
    Color get_color();
    void set_color(Color color);
    void set_score(int score);
    void incr_speed() override;
    void render(float dt) override;
    Character();
    ~Character();
};
