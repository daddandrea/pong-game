#include "../include/game.h"
#include "../include/scene_manager.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>

TextRenderer* text_renderer;
SceneManager scene_manager;
bool is_running;

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOV_DEGREES, ASPECT_RATIO, NEAR_CLIPPING_PLANE, FAR_CLIPPING_PLANE);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}

void draw_cage(Color color) {
    glLineWidth(CAGE_LINE_WIDTH);
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_LINE_LOOP);
        glVertex3f(-get_cage_half_w(),-get_cage_half_h(), 0.0);
        glVertex3f( get_cage_half_w(),-get_cage_half_h(), 0.0);
        glVertex3f( get_cage_half_w(), get_cage_half_h(), 0.0);
        glVertex3f(-get_cage_half_w(), get_cage_half_h(), 0.0);
    glEnd();
}
void display() {
    auto current_time = std::chrono::high_resolution_clock::now();
    static auto last_time = current_time;

    std::chrono::duration<float> dt = current_time - last_time;
    last_time = current_time;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, Z_INITIAL_TRANSLATE);

    switch (scene_manager.get_scene()) {
        case S_MAIN_MENU:
            scene_manager.render_main_menu(dt.count());
            break;
        case S_GAME_LOOP:
            scene_manager.render_game_loop(dt.count());
            break;
        case S_GAME_MENU:
            scene_manager.render_game_menu(dt.count());
            break;
        case S_END_CREDITS:
            scene_manager.render_credits(dt.count());
            break;
        case S_NONE:
        default:
            scene_manager.clear_game_data();
            is_running = false;
            break;
    }
}
void render_game() {
    srand(static_cast<unsigned>(time(0)));

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    SDL_Window* window = SDL_CreateWindow("Pong game",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH,
                                          WINDOW_HEIGHT,
                                          SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);


    is_running = true;
    SDL_Event event;

    init();
    scene_manager.init();

    while (is_running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    is_running = false;
                    break;
                case SDL_KEYDOWN:
                    if (Player* player1 = dynamic_cast<Player*>(scene_manager.get_game_data()->get_character1())) {
                        player1->manage_key_down_movement(event.key.keysym.sym);
                        player1->manage_key_down_actions(event.key.keysym.sym, *scene_manager.get_game_data()->get_ball());
                    }
                    if (Player* player2 = dynamic_cast<Player*>(scene_manager.get_game_data()->get_character2())) {
                        player2->manage_key_down_movement(event.key.keysym.sym);
                        player2->manage_key_down_actions(event.key.keysym.sym, *scene_manager.get_game_data()->get_ball());
                    }
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        if (scene_manager.get_scene() == S_GAME_LOOP)
                            scene_manager.set_scene(S_GAME_MENU);
                        else if (scene_manager.get_scene() == S_GAME_MENU)
                            scene_manager.set_scene(S_GAME_LOOP);
                    }
                    break;
                case SDL_KEYUP:
                    if (Player* player1 = dynamic_cast<Player*>(scene_manager.get_game_data()->get_character1())) {
                        player1->manage_key_up(event.key.keysym.sym);
                    }
                    if (Player* player2 = dynamic_cast<Player*>(scene_manager.get_game_data()->get_character2())) {
                        player2->manage_key_up(event.key.keysym.sym);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (scene_manager.get_scene() == S_MAIN_MENU || scene_manager.get_scene() == S_GAME_MENU) {
                        if (event.button.button == SDL_BUTTON_LEFT) {
                            int x = event.button.x;
                            int y = event.button.y;
                            Vec2 gl_coords = text_to_opengl_coords(x, y, WINDOW_WIDTH, WINDOW_HEIGHT);

                            bool start_button_clicked = scene_manager.get_game_data()->get_start_button()->get_collider()->contains(gl_coords);
                            bool exit_button_clicked = scene_manager.get_game_data()->get_exit_button()->get_collider()->contains(gl_coords);
                            bool char1_button_clicked = scene_manager.get_game_data()->get_char1_button()->get_collider()->contains(gl_coords);
                            bool char2_button_clicked = scene_manager.get_game_data()->get_char2_button()->get_collider()->contains(gl_coords);

                            if (start_button_clicked) {
                                scene_manager.clear_game_data();
                                scene_manager.init();
                                scene_manager.set_scene(S_GAME_LOOP);  // Transition to game loop
                            } else if (exit_button_clicked) {
                                scene_manager.set_scene(S_NONE);
                            } else if (char1_button_clicked) {
                                if (scene_manager.get_game_data()->get_character1()->is_player()) {
                                    scene_manager.get_game_data()->set_is_char1_player(false);
                                    scene_manager.get_game_data()->get_char1_button()->set_type(B_T_CPU_1);
                                } else {
                                    scene_manager.get_game_data()->set_is_char1_player(true);
                                    scene_manager.get_game_data()->get_char1_button()->set_type(B_T_PLAYER_1);
                                }
                            } else if (char2_button_clicked) {
                                if (scene_manager.get_game_data()->get_character2()->is_player()) {
                                    scene_manager.get_game_data()->set_is_char2_player(false);
                                    scene_manager.get_game_data()->get_char2_button()->set_type(B_T_CPU_2);
                                } else {
                                    scene_manager.get_game_data()->set_is_char2_player(true);
                                    scene_manager.get_game_data()->get_char2_button()->set_type(B_T_PLAYER_2);
                                }
                            }
                        }
                        break;
                    }

            }
        }
        display();
        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
