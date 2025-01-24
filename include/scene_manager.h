#pragma once

#include "text_renderer.h"
#include "ball.h"
#include "player.h"
#include "cpu.h"
#include "button.h"
#include "essentials.h"
#include <ostream>

enum Scene { S_NONE, S_MAIN_MENU, S_GAME_LOOP, S_GAME_MENU, S_END_CREDITS };
std::ostream& operator<<(std::ostream& os, Scene scene);

class GameData {
private:
    Ball* ball;
    Character* character1;
    Character* character2;
    bool is_char1_player;
    bool is_char2_player;
    TextRenderer* text_renderer;
    Button* start_button;
    Button* exit_button;
    Button* char1_button;
    Button* char2_button;
public:
    GameData();
    Ball* get_ball();
    void set_ball(Ball* ball);
    Character* get_character1();
    void set_character1(Character* character1);
    bool get_is_char1_player();
    void set_is_char1_player(bool is_char1_player);
    Character* get_character2();
    void set_character2(Character* character2);
    bool get_is_char2_player();
    void set_is_char2_player(bool is_char2_player);
    TextRenderer* get_text_renderer();
    void set_text_renderer(TextRenderer* text_renderer);
    Button* get_start_button();
    void set_start_button(Button* start_button);
    Button* get_exit_button();
    void set_exit_button(Button* exit_button);
    Button* get_char1_button();
    void set_char1_button(Button* exit_button);
    Button* get_char2_button();
    void set_char2_button(Button* exit_button);
};

class SceneManager {
private:
    GameData* game_data;
    Scene scene;
    void draw_cage(Color color);
    void handle_collisions();
    bool is_game_over();
public:
    SceneManager();
    SceneManager(GameData game_data);
    GameData* get_game_data();
    Scene get_scene();
    void set_scene(Scene scene);
    void init();
    void clear_game_data();
    void render_main_menu(float dt);
    void render_game_loop(float dt);
    void render_game_menu(float dt);
    void render_credits(float dt);
};
