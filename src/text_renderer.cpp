#include "../include/text_renderer.h"
#include <GL/gl.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

TextRenderer::TextRenderer(int win_w, int win_h)
    : m_Font(nullptr), m_win_width(win_w), m_win_height(win_h) {
    if (TTF_WasInit() == 0) {
        if (TTF_Init() == -1) {
            std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        }
    }
}
TextRenderer::~TextRenderer() {
    if (m_Font) {
        TTF_CloseFont(m_Font);
        m_Font = nullptr;
    }
    TTF_Quit();
}
bool TextRenderer::load_font(const std::string& font_path, int font_size) {
    m_Font = TTF_OpenFont(font_path.c_str(), font_size);
    if (!m_Font) {
        std::cerr << "Failed to load font: " << TTF_GetError << std::endl;
        return false;
    }
    return true;
}
void TextRenderer::render_text(const std::string& text, int x, int y, SDL_Color color) {
    if (!m_Font) {
        std::cerr << "Font not loaded!" << std::endl;
        return;
    }

    SDL_Surface* text_surface = TTF_RenderText_Blended(m_Font, text.c_str(), color);
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

    std::cerr << "BytesPerPixel=" << (int)conv_surface->format->BytesPerPixel << "\n";
    std::cerr << "Rmask=0x" << std::hex << conv_surface->format->Rmask << std::dec << "\n";
    std::cerr << "w=" << conv_surface->w << ", h=" << conv_surface->h << "\n";

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
