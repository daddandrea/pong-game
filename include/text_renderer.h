#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class TextRenderer {
private:
    TTF_Font* m_Font;
    int m_win_width;
    int m_win_height;
public:
    TextRenderer(int win_w, int win_h);
    ~TextRenderer();
    bool load_font(const std::string& font_path, int font_size);
    void render_text(const std::string& text, int x, int y, SDL_Color color);
};
