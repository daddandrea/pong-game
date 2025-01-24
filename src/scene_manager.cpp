#include "../include/scene_manager.h"
#include <GL/gl.h>
#include <SDL2/SDL_pixels.h>
#include <iostream>
#include <string>

std::ostream &operator<<(std::ostream &os, Scene scene) {
  switch (scene) {
  case S_NONE:
    os << "NONE";
    break;
  case S_MAIN_MENU:
    os << "MAIN_MENU";
    break;
  case S_GAME_LOOP:
    os << "GAME_LOOP";
    break;
  case S_GAME_MENU:
    os << "GAME_MENU";
    break;
  case S_END_CREDITS:
    os << "END_CREDITS";
    break;
  }
  return os;
}

GameData::GameData()
    : ball(nullptr), character1(nullptr), character2(nullptr),
      text_renderer(nullptr), start_button(nullptr),
      exit_button(nullptr), char1_button(nullptr), char2_button(nullptr),
      is_char1_player(true), is_char2_player(false) {}
Ball *GameData::get_ball() { return this->ball; }
void GameData::set_ball(Ball *ball) { this->ball = ball; }
Character *GameData::get_character1() { return this->character1; }
void GameData::set_character1(Character *character1) { this->character1 = character1; }
bool GameData::get_is_char1_player() { return this->is_char1_player; }
void GameData::set_is_char1_player(bool is_char1_player) { this->is_char1_player = is_char1_player; }
Character *GameData::get_character2() { return this->character2; }
void GameData::set_character2(Character *character2) { this->character2 = character2; }
bool GameData::get_is_char2_player() { return this->is_char2_player; }
void GameData::set_is_char2_player(bool is_char2_player) { this->is_char2_player = is_char2_player; }
TextRenderer *GameData::get_text_renderer() { return this->text_renderer; }
void GameData::set_text_renderer(TextRenderer *text_renderer) { this->text_renderer = text_renderer; }
Button* GameData::get_start_button() { return this->start_button; }
void GameData::set_start_button(Button* start_button) { this->start_button = start_button; }
Button* GameData::get_exit_button() { return this->exit_button; }
void GameData::set_exit_button(Button* exit_button) { this->exit_button = exit_button; }
Button* GameData::get_char1_button() { return this->char1_button; }
void GameData::set_char1_button(Button* char1_button) { this->char1_button = char1_button; }
Button* GameData::get_char2_button() { return this->char2_button; }
void GameData::set_char2_button(Button* char2_button) { this->char2_button = char2_button; }

SceneManager::SceneManager() : game_data(new GameData()), scene(S_MAIN_MENU) {}

Scene SceneManager::get_scene() { return scene; }
void SceneManager::set_scene(Scene scene) { this->scene = scene; }
GameData *SceneManager::get_game_data() { return game_data; }
void SceneManager::draw_cage(Color color) {
    glLineWidth(CAGE_LINE_WIDTH);
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_LINE_LOOP);
        glVertex3f(-get_cage_half_w(),-get_cage_half_h(), 0.0);
        glVertex3f( get_cage_half_w(),-get_cage_half_h(), 0.0);
        glVertex3f( get_cage_half_w(), get_cage_half_h(), 0.0);
        glVertex3f(-get_cage_half_w(), get_cage_half_h(), 0.0);
    glEnd();
}
void SceneManager::handle_collisions() {
    if (game_data->get_ball()->get_collider()->is_colliding(*(game_data->get_character1()->get_collider())) ||
        game_data->get_ball()->get_collider()->is_colliding(*(game_data->get_character2()->get_collider()))) {
        if (game_data->get_ball()->get_hor_mov_state() == B_H_M_LEFT)
            game_data->get_ball()->set_hor_mov_state(B_H_M_RIGHT);
        else if (game_data->get_ball()->get_hor_mov_state() == B_H_M_RIGHT)
            game_data->get_ball()->set_hor_mov_state(B_H_M_LEFT);
    }

    if (game_data->get_ball()->get_collider()->is_colliding_with_cage() == CAGE_SIDE_LEFT) {
        if (game_data->get_character1()->get_side() == C_S_RIGHT) {
            game_data->get_character1()->set_score(game_data->get_character1()->get_score() + 1);
        } else if (game_data->get_character2()->get_side() == C_S_RIGHT) {
            game_data->get_character2()->set_score(game_data->get_character2()->get_score() + 1);
        }
    }
    else if (game_data->get_ball()->get_collider()->is_colliding_with_cage() == CAGE_SIDE_RIGHT) {
        if (game_data->get_character1()->get_side() == C_S_LEFT) {
            game_data->get_character1()->set_score(game_data->get_character1()->get_score() + 1);
        } else if (game_data->get_character2()->get_side() == C_S_LEFT) {
            game_data->get_character2()->set_score(game_data->get_character2()->get_score() + 1);
        }
    }
}

bool SceneManager::is_game_over() {
    return game_data->get_character1()->get_score() >= 5 || game_data->get_character2()->get_score() >= 5;
}
void SceneManager::init() {
    Ball* ball = new Ball();
    Character* character1 = game_data->get_is_char1_player() ? 
        static_cast<Character*>(new Player()) : 
        static_cast<Character*>(new Cpu(*ball, true));
    Character* character2 = game_data->get_is_char2_player() ? 
        static_cast<Character*>(new Player()) : 
        static_cast<Character*>(new Cpu(*ball, true));
    TextRenderer* text_renderer = new TextRenderer(WINDOW_WIDTH, WINDOW_HEIGHT);
    Button* start_button = new Button(B_T_START_GAME, Color {0.0, 1.0, 0.0});
    Button* exit_button = new Button(B_T_EXIT_GAME, Color {1.0, 1.0, 0.0});
    Button* char_1_button = new Button(B_T_PLAYER_1, Color {0.0, 1.0, 1.0});
    Button* char_2_button = new Button(B_T_CPU_2, Color {0.0, 1.0, 1.0});

    if (!text_renderer->load_font("main", "/usr/share/fonts/TTF/JetBrainsMonoNerdFont-Regular.ttf", 100)) {
        std::cerr << "Failed to load font" << std::endl;
        return;
    }
    if (!text_renderer->load_font("game_object", "/usr/share/fonts/TTF/JetBrainsMonoNerdFont-Regular.ttf", 20)) {
        std::cerr << "Failed to load font" << std::endl;
        return;
    }
    if (!text_renderer->load_font("button", "/usr/share/fonts/TTF/JetBrainsMonoNerdFont-Regular.ttf", 40)) {
        std::cerr << "Failed to load font" << std::endl;
        return;
    }
    game_data->set_character1(character1);
    game_data->set_character2(character2);
    game_data->set_ball(ball);
    game_data->set_text_renderer(text_renderer);
    game_data->set_start_button(start_button);
    game_data->set_exit_button(exit_button);
    game_data->set_char1_button(char_1_button);
    game_data->set_char2_button(char_2_button);
}
void SceneManager::clear_game_data() {
    if (game_data->get_character1()) {
        delete game_data->get_character1();
        game_data->set_character1(nullptr);
    }
    if (game_data->get_character2()) {
        delete game_data->get_character2();
        game_data->set_character2(nullptr);
    }
    if (game_data->get_ball()) {
        delete game_data->get_ball();
        game_data->set_ball(nullptr);
    }
    if (game_data->get_text_renderer()) {
        delete game_data->get_text_renderer();
        game_data->set_text_renderer(nullptr);
    }
}
void SceneManager::render_main_menu(float dt) {
    game_data->get_start_button()->render(game_data->get_text_renderer());
    game_data->get_exit_button()->render(game_data->get_text_renderer());
    game_data->get_char1_button()->render(game_data->get_text_renderer());
    game_data->get_char2_button()->render(game_data->get_text_renderer());
}
void SceneManager::render_game_loop(float dt) {
    if (!is_game_over()) {
        Color cage_color = {1.0, 1.0, 1.0};
        draw_cage(cage_color);

        if (scene == S_GAME_LOOP) {
            handle_collisions();
            game_data->get_ball()->render(dt);
            game_data->get_character1()->render(dt);
            if (game_data->get_text_renderer()->set_active_font("main"))
                game_data->get_text_renderer()->render_text(
                    std::to_string(game_data->get_character1()->get_score()),
                    game_data->get_character1()->get_pos().x + 3.0,
                    get_cage_half_h(),
                    SDL_Color {255, 255, 255, 100});
            game_data->get_character2()->render(dt);
            if (game_data->get_text_renderer()->set_active_font("main"))
                game_data->get_text_renderer()->render_text(
                    std::to_string(game_data->get_character2()->get_score()),
                    game_data->get_character2()->get_pos().x - 3.0,
                    get_cage_half_h(),
                    SDL_Color {255, 255, 255, 100});
        } else if (scene == S_GAME_MENU) {
            render_game_menu(dt);
        }
    } else {
        scene = S_END_CREDITS;
    }
}
void SceneManager::render_game_menu(float dt) {
    if (game_data->get_text_renderer()->set_active_font("main")) {
        std::string text = "Pause...";
        game_data->get_text_renderer()->render_text(text, -get_cage_half_w(), get_cage_half_h(), SDL_Color {255, 255, 255, 255});
        game_data->get_exit_button()->render(game_data->get_text_renderer());
    }
}
void SceneManager::render_credits(float dt) {
}
