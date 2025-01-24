#pragma once

#include "../include/essentials.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include <string>
#include <utility>

class TextRenderer {
private:
    std::map<std::string, TTF_Font*> m_Fonts;
    TTF_Font* m_Active_Font;
    int m_win_width;
    int m_win_height;
public:
    TextRenderer(int win_w, int win_h);
    TextRenderer();
    ~TextRenderer();
    bool is_font_loaded(const std::string& font_name) const;
    bool load_font(const std::string& font_name, const std::string& font_path, int font_size);
    bool set_active_font(const std::string& font_name);
    void render_text(const std::string& text, float gl_x, float gl_y, SDL_Color color);
};
