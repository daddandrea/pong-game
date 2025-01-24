#include "../include/text_renderer.h"
#include <GL/gl.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <utility>

TextRenderer::TextRenderer(int win_w, int win_h)
    : m_Active_Font(nullptr), m_win_width(win_w), m_win_height(win_h) {
    if (TTF_WasInit() == 0) {
        if (TTF_Init() == -1) {
            std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        }
    }
}
TextRenderer::TextRenderer()
    : m_Active_Font(nullptr), m_win_width(WINDOW_WIDTH), m_win_height(WINDOW_HEIGHT) {
    if (TTF_WasInit() == 0) {
        if (TTF_Init() == -1) {
            std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        }
    }
}
TextRenderer::~TextRenderer() {
    if (m_Active_Font) {
        TTF_CloseFont(m_Active_Font);
        m_Active_Font = nullptr;
    }
    TTF_Quit();
}
bool TextRenderer::is_font_loaded(const std::string& font_name) const {
    return m_Fonts.find(font_name) != m_Fonts.end();
}
bool TextRenderer::load_font(const std::string& font_name, const std::string& font_path, int font_size) {
    if (m_Fonts.find(font_name) == m_Fonts.end()) {
        TTF_Font* new_font = TTF_OpenFont(font_path.c_str(), font_size);
        if (!new_font) {
            std::cerr << "Failed to load font: " << font_path << " - " << TTF_GetError() << std::endl;
            return false;
        }
        m_Fonts[font_name] = new_font;
    }
    m_Active_Font = m_Fonts[font_name];
    return true;
}
bool TextRenderer::set_active_font(const std::string& font_name) {
    auto it = m_Fonts.find(font_name);
    if (it == m_Fonts.end()) {
        std::cerr << "Font not loaded: " << font_name << std::endl;
        return false;
    }

    m_Active_Font = it->second;
    return true;
}
void TextRenderer::render_text(const std::string& text, float gl_x, float gl_y, SDL_Color color) {
    float x_ndc = gl_x / get_viewport_half_w();
    float y_ndc = gl_y / get_viewport_half_h();

    float text_x = ((x_ndc + 1.0f) / 2.0f) * WINDOW_WIDTH;
    float text_y = ((1.0f - y_ndc) / 2.0f) * WINDOW_HEIGHT;

    int x = static_cast<int>(text_x);
    int y = static_cast<int>(text_y);

    if (!m_Active_Font) {
        std::cerr << "No active font loaded!" << std::endl;
        return;
    }

    SDL_Surface* text_surface = TTF_RenderText_Blended(m_Active_Font, text.c_str(), color);
    if (!text_surface) {
        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Surface* conv_surface = SDL_ConvertSurfaceFormat(text_surface, SDL_PIXELFORMAT_RGBA32, 0);
    SDL_FreeSurface(text_surface);
    if (!conv_surface) {
        std::cerr << "Failed to convert text surface to RGBA32." << std::endl;
        return;
    }

    GLuint texture_id = 0;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    GLenum texture_format = GL_RGBA;
    if (conv_surface->format->BytesPerPixel == 4) {
        if (conv_surface->format->Rmask == 0x000000ff)
            texture_format = GL_RGBA;
        else
            texture_format = GL_BGRA;
    } else {
        std::cerr << "Warning: text surface is not 32-bit." << std::endl;
    }

    glTexImage2D(
        GL_TEXTURE_2D, 
        0, 
        GL_RGBA, 
        conv_surface->w, 
        conv_surface->h, 
        0, 
        texture_format, 
        GL_UNSIGNED_BYTE, 
        conv_surface->pixels
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, m_win_width, m_win_height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        // Top-left
        glTexCoord2f(0.0f, 0.0f); 
        glVertex2f((GLfloat)x, (GLfloat)y);

        // Top-right
        glTexCoord2f(1.0f, 0.0f); 
        glVertex2f((GLfloat)x + conv_surface->w, (GLfloat)y);

        // Bottom-right
        glTexCoord2f(1.0f, 1.0f); 
        glVertex2f((GLfloat)x + conv_surface->w, (GLfloat)y + conv_surface->h);

        // Bottom-left
        glTexCoord2f(0.0f, 1.0f); 
        glVertex2f((GLfloat)x, (GLfloat)y + conv_surface->h);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glDeleteTextures(1, &texture_id);
    SDL_FreeSurface(conv_surface);
}
