#include "../include/game.h"
#include "../include/essentials.h"
#include "../include/ball.h"
#include "../include/player.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include <chrono>
#include <cmath>
#include <cstdlib>

Ball ball = Ball();
Player player = Player();
Player player2 = Player();

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
        glVertex3f(-CAGE_HALF_WIDTH,-CAGE_HALF_HEIGHT, 0.0);
        glVertex3f( CAGE_HALF_WIDTH,-CAGE_HALF_HEIGHT, 0.0);
        glVertex3f( CAGE_HALF_WIDTH, CAGE_HALF_HEIGHT, 0.0);
        glVertex3f(-CAGE_HALF_WIDTH, CAGE_HALF_HEIGHT, 0.0);
    glEnd();
}

void handle_collisions() {
    if (ball.get_collider()->is_colliding(*player.get_collider())) {
        if (ball.get_hor_mov_state() == B_H_M_LEFT) {
            ball.set_hor_mov_state(B_H_M_RIGHT);
        } else if (ball.get_hor_mov_state() == B_H_M_RIGHT) {
            ball.set_hor_mov_state(B_H_M_LEFT);
        }
    }
}

void display() {
    auto current_time = std::chrono::high_resolution_clock::now();
    static auto last_time = current_time;

    std::chrono::duration<float> dt = current_time - last_time;
    last_time = current_time;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0, 0.0, Z_INITIAL_TRANSLATE);
    Color cage_color = {1.0, 1.0, 1.0};
    draw_cage(cage_color);

    handle_collisions();

    ball.render(dt.count());
    player.render(dt.count());
    player2.render(dt.count());
}

void render_game() {
    srand(static_cast<unsigned>(time(0)));

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    SDL_Window* window = SDL_CreateWindow("Pong game",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1920,
                                          1080,
                                          SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);

    bool is_running = true;
    SDL_Event event;

    init();

    while (is_running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    is_running = false;
                    break;
                case SDL_KEYDOWN:
                    player.manage_key_down_movement(event.key.keysym.sym);
                    player.manage_key_down_actions(event.key.keysym.sym, ball);
                    break;
                case SDL_KEYUP:
                    player.manage_key_up(event.key.keysym.sym);
                    break;
            }
        }
        display();
        SDL_GL_SwapWindow(window);
    }
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
