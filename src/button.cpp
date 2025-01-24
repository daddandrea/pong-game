#include "../include/button.h"
#include <GL/gl.h>
#include <SDL2/SDL_pixels.h>
#include <iostream>
#include <stdexcept>

std::ostream &operator<<(std::ostream &os, ButtonType type) {
    switch (type) {
        case B_T_START_GAME:
            os << "START_GAME";
            break;
        case B_T_EXIT_GAME:
            os << "EXIT_GAME";
            break;
        case B_T_PLAYER_1:
            os << "PLAYER_1";
            break;
        case B_T_PLAYER_2:
            os << "PLAYER_2";
            break;
        case B_T_CPU_1:
            os << "CPU_1";
            break;
        case B_T_CPU_2:
            os << "CPU_2";
            break;
        default:
            os << "UNKNOWN";
            break;
    }
    return os;
}

Button::Button(ButtonType type, Color color) :
    half_w(BUTTON_HALF_WIDTH),
    half_h(BUTTON_HALF_HEIGHT),
    color(color),
    type(type) {
    switch (type) {
        case B_T_START_GAME:
            pos = Vec2 {BUTTON_STANDARD_X, BUTTON_START_STANDARD_Y};
            break;
        case B_T_EXIT_GAME:
            pos = Vec2 {BUTTON_STANDARD_X, BUTTON_EXIT_STANDARD_Y}; 
            break;
        case B_T_PLAYER_1:
        case B_T_CPU_1:
            pos = Vec2 {BUTTON_CHAR_1_X, BUTTON_STANDARD_Y}; 
            break;
        case B_T_PLAYER_2:
        case B_T_CPU_2:
            pos = Vec2 {BUTTON_CHAR_2_X, BUTTON_STANDARD_Y}; 
            break;
    }

    collider = std::make_unique<RectangleCollider>(
        Vec2{pos.x, pos.y},
        half_w,
        half_h
    );
}

Button::~Button() {}

std::unique_ptr<Collider>& Button::get_collider() { return this->collider; }
Vec2 Button::get_pos() { return this->pos; }
void Button::set_pos(Vec2 pos) { this->pos = pos; }
float Button::get_half_w() { return this->half_w; }
void Button::set_half_w(float half_w) { this->half_w = half_w; }
float Button::get_half_h() { return this->half_h; }
void Button::set_half_h(float half_h) { this->half_h = half_h; }
Color Button::get_color() { return this->color; }
void Button::set_color(Color color) { this->color = color; }
ButtonType Button::get_type() { return this->type; }
void Button::set_type(ButtonType target_type) {
    switch (this->type) {
        case B_T_PLAYER_1: this->type = B_T_CPU_1; break;
        case B_T_CPU_1: this->type = B_T_PLAYER_1; break;
        case B_T_PLAYER_2: this->type = B_T_CPU_2; break;
        case B_T_CPU_2: this->type = B_T_PLAYER_2; break;
        default:
            throw std::runtime_error("Invalid type change for this button.");
    }
}

void Button::draw_button() {
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_QUADS);
        glVertex3f(pos.x - half_w, pos.y - half_h, 0.0);
        glVertex3f(pos.x + half_w, pos.y - half_h, 0.0);
        glVertex3f(pos.x + half_w, pos.y + half_h, 0.0);
        glVertex3f(pos.x - half_w, pos.y + half_h, 0.0);
    glEnd();
}
void Button::draw_text(TextRenderer* text_renderer) {
    if (text_renderer->set_active_font("button")) {
        std::string text;
        switch (type) {
            case B_T_START_GAME: {
                text = "Start Game";
            }
                break;
            case B_T_EXIT_GAME: {
                text = "Exit Game";
            }
                break;
            case B_T_PLAYER_1: {
                text = "1 - Player";
            }
                break;
            case B_T_PLAYER_2: {
                text = "2 - Player";
            }
                break;
            case B_T_CPU_1: {
                text = "1 - Cpu";
            }
                break;
            case B_T_CPU_2: {
                text = "2 - Cpu";
            }
                break;
        }
        text_renderer->render_text(text, pos.x - BUTTON_HALF_WIDTH + MARGIN * 3, pos.y, SDL_Color {0, 0, 0, 255});
    }
}
void Button::render(TextRenderer* text_renderer) {
    glPushMatrix();
    draw_button();
    draw_text(text_renderer);
    glPopMatrix();
    if (collider) {
        collider->set_position(pos);
    }
}
