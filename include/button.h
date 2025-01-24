#pragma once

#include "collider.h"
#include "essentials.h"
#include "text_renderer.h"
#include <memory>
#define BUTTON_STANDARD_X 0.0f
#define BUTTON_STANDARD_Y 0.0f
#define BUTTON_START_STANDARD_Y 3.0f
#define BUTTON_EXIT_STANDARD_Y -3.0f
#define BUTTON_CHAR_1_X -3.0
#define BUTTON_CHAR_2_X 3.0
#define BUTTON_HALF_WIDTH  2.0f
#define BUTTON_HALF_HEIGHT 1.0f

enum ButtonType { B_T_START_GAME, B_T_EXIT_GAME, B_T_PLAYER_1, B_T_PLAYER_2, B_T_CPU_1, B_T_CPU_2 };
std::ostream &operator<<(std::ostream &os, ButtonType type);

class Button {
private:
    std::unique_ptr<Collider> collider;
    Vec2 pos;
    float half_w;
    float half_h;
    Color color;
    ButtonType type;
    void draw_button();
    void draw_text(TextRenderer* text_renderer);
public:
    std::unique_ptr<Collider> &get_collider();
    Vec2 get_pos();
    void set_pos(Vec2 pos);
    float get_half_w();
    void set_half_w(float half_w);
    float get_half_h();
    void set_half_h(float half_h);
    Color get_color();
    void set_color(Color color);
    ButtonType get_type();
    void set_type(ButtonType type);
    void render(TextRenderer* text_renderer);
    Button(ButtonType type, Color color);
    virtual ~Button();
};
