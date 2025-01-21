#include "../include/menu.h"

GameMenu::GameMenu() : 
    current_state(G_S_MENU),
    selected_mode(G_M_NONE),
    ball_color{1.0f, 0.0f, 0.0f},
    left_player_color{0.0f, 1.0f, 0.0f},
    right_player_color{0.0f, 1.0f, 0.0f},
    show_main_menu(true),
    show_pause_menu(false) {}

void GameMenu::init(SDL_Window* window, SDL_GLContext gl_context) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL2_Init();
}

void GameMenu::cleanup() {
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void GameMenu::render_main_menu() {
    if (!show_main_menu) return;

    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));

    ImGui::Begin("Main Menu", nullptr, 
                 ImGuiWindowFlags_AlwaysAutoResize | 
                 ImGuiWindowFlags_NoMove | 
                 ImGuiWindowFlags_NoCollapse);

    if (ImGui::Button("Player vs Player", ImVec2(200, 40))) {
        selected_mode = G_M_PVP;
        current_state = G_S_PLAYING;
        show_main_menu = false;
    }

    if (ImGui::Button("Player vs CPU", ImVec2(200, 40))) {
        selected_mode = G_M_CPU;
        current_state = G_S_PLAYING;
        show_main_menu = false;
    }

    ImGui::Separator();

    ImGui::Text("Ball Color");
    ImGui::ColorEdit3("##Ball", &ball_color.r);

    ImGui::Text("Left Player Color");
    ImGui::ColorEdit3("##Left", &left_player_color.r);

    ImGui::Text("Right Player Color");
    ImGui::ColorEdit3("##Right", &right_player_color.r);

    ImGui::Separator();

    if (ImGui::Button("Exit", ImVec2(200, 40))) {
        SDL_Event quit_event;
        quit_event.type = SDL_QUIT;
        SDL_PushEvent(&quit_event);
    }

    ImGui::End();
}

void GameMenu::render_pause_menu() {
    if (!show_pause_menu) return;

    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f),
                            ImGuiCond_Always, ImVec2(0.5f, 0.5f));

    ImGui::Begin("Pause Menu", nullptr, 
                 ImGuiWindowFlags_AlwaysAutoResize | 
                 ImGuiWindowFlags_NoMove | 
                 ImGuiWindowFlags_NoCollapse);

    if (ImGui::Button("Resume", ImVec2(200, 40))) {
        show_pause_menu = false;
        current_state = G_S_PLAYING;
    }

    if (ImGui::Button("Return to Main Menu", ImVec2(200, 40))) {
        show_pause_menu = false;
        show_main_menu = true;
        current_state = G_S_MENU;
        selected_mode = G_M_NONE;
    }

    if (ImGui::Button("Exit", ImVec2(200, 40))) {
        SDL_Event quit_event;
        quit_event.type = SDL_QUIT;
        SDL_PushEvent(&quit_event);
    }

    ImGui::End();
}

void GameMenu::handle_event(const SDL_Event& event) {
    ImGui_ImplSDL2_ProcessEvent(&event);

    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        if (current_state == G_S_PLAYING) {
            show_pause_menu = true;
            current_state = G_S_PAUSED;
        } else if (current_state == G_S_PAUSED) {
            show_pause_menu = false;
            current_state = G_S_PLAYING;
        }
    }
}

void GameMenu::render() {
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    if (current_state == G_S_MENU) {
        render_main_menu();
    } else if (current_state == G_S_PAUSED) {
        render_pause_menu();
    }

    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

GameState GameMenu::get_state() const { return current_state; }
GameMode GameMenu::get_mode() const { return selected_mode; }
void GameMenu::set_state(GameState state) { this->current_state = state; }
Color GameMenu::get_ball_color() const { return ball_color; }
Color GameMenu::get_left_player_color() const { return left_player_color; }
Color GameMenu::get_right_player_color() const { return right_player_color; }
