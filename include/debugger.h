#pragma once

#include "../include/text_renderer.h"

class Debugger {
public:
    static void draw_debug_info_pos(const Vec2& position, TextRenderer& text_renderer, SDL_Color color);
    virtual ~Debugger() = default;
};
