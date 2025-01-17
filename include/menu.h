#pragma once

#include "../external/imgui/imgui.h"
#include "../external/imgui/imgui_impl_sdl2.h"
#include "../external/imgui/imgui_impl_opengl2.h"
#include "essentials.h"

#include <SDL2/SDL.h>

enum GameMode {
    G_M_NONE,
    G_M_PVP,
    G_M_CPU
};

enum GameState {
    G_S_MENU,
    G_S_PLAYING,
    G_S_PAUSED
};

class GameMenu {
private:
    GameState current_state;
    GameMode selected_mode;
    Color ball_color;
    Color left_player_color;
    Color right_player_color;
    bool show_main_menu;
    bool show_pause_menu;

public:
    GameMenu();
    void init(SDL_Window* window, SDL_GLContext gl_context);
    void cleanup();
    void render_main_menu();
    void render_pause_menu();
    void handle_event(const SDL_Event& event);
    void render();
    GameState get_state() const;
    GameMode get_mode() const;
    Color get_ball_color() const;
    Color get_left_player_color() const;
    Color get_right_player_color() const;
};
