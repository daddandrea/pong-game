#include "../include/debugger.h"

void Debugger::draw_debug_info_pos(const Vec2 &position, TextRenderer &text_renderer, SDL_Color color) {
  std::string debug_text = "(" + std::to_string((int)position.x) + ", " +
                           std::to_string((int)position.y) + ")";
  text_renderer.render_text(debug_text, position.x,
                            position.y, color);
}
