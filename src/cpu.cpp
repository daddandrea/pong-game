#include "../include/cpu.h"
#include "../include/ball.h"

Cpu::Cpu(Ball& ball_ref, bool can_parry) : ball_ref(ball_ref), can_parry(can_parry) {
    color = Color {0.0, 0.0, 1.0};
}

void Cpu::decide_movement() {
    if (pos.y != ball_ref.get_pos().y) {
        if (pos.y < ball_ref.get_pos().y) {
            ver_mov_state = C_V_M_MOVING_UP;
        } else {
            ver_mov_state = C_V_M_MOVING_DOWN;
        }
    } else {
        ver_mov_state = C_V_M_STATIONARY;
    }
}
void Cpu::decide_actions() {
    bool is_in_parry_range = collider->is_in_parry_range(*ball_ref.get_collider());

    if (is_in_parry_range && !is_parry_on_cooldown()) {
        if (rand() % 10 < 3) {
            ball_ref.bounce_from_parry(*this);
        }
        last_parry_time = std::chrono::steady_clock::now();
    }
}
void Cpu::render(float dt) {
    Character::render(dt);
    decide_movement();
    if (can_parry)
        decide_actions();
}
