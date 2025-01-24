#include "../include/essentials.h"
#include <iostream>

float CAGE_HALF_HEIGHT = (std::floorf(float(std::abs(Z_INITIAL_TRANSLATE)) * std::tanf((FOV_DEGREES * M_PIf / 180.0f) / 2.0f)));
float CAGE_HALF_WIDTH = std::floorf(CAGE_HALF_HEIGHT * (ASPECT_RATIO));

std::ostream& operator<<(std::ostream& os, CageSide side) {
    switch (side) {
        case CAGE_SIDE_NONE: os << "NONE"; break;
        case CAGE_SIDE_TOP: os << "TOP"; break;
        case CAGE_SIDE_BOTTOM: os << "BOTTOM"; break;
        case CAGE_SIDE_RIGHT: os << "RIGHT"; break;
        case CAGE_SIDE_LEFT: os << "LEFT"; break;
        default: os << "UNKNOWN"; break;
    }
    return os;
}

float get_viewport_half_w() { return std::abs(Z_INITIAL_TRANSLATE) * std::tan((FOV_DEGREES * M_PI / 180.0f) / 2.0f) * ASPECT_RATIO; }
float get_viewport_half_h() { return std::abs(Z_INITIAL_TRANSLATE) * std::tan((FOV_DEGREES * M_PI / 180.0f) / 2.0f); }

float get_cage_half_h() { return CAGE_HALF_HEIGHT; }
float get_cage_half_w() { return CAGE_HALF_WIDTH; }

Vec2 opengl_to_text_coords(float x, float y, int window_width, int window_height) {
    Vec2 screen_coords;

    float x_ndc = x / get_cage_half_w();
    float y_ndc = y / get_cage_half_h();
    screen_coords.x = ((x_ndc + 1.0f) / 2.0f) * window_width;
    screen_coords.y = window_height - ((y_ndc + 1.0f) / 2.0f) * window_height;

    return screen_coords;
}

Vec2 old_text_to_opengl_coords(float x_screen, float y_screen, int window_width, int window_height) {
    Vec2 ndc_coords;
    ndc_coords.x = (2.0f * x_screen / window_width) - 1.0f;
    ndc_coords.y = (2.0f * (window_height - y_screen) / window_height) - 1.0f;
    return ndc_coords;
}
Vec2 text_to_opengl_coords(float x_screen, float y_screen,
                           int window_width, int window_height)
{
    // 1) Convert from [0..window_width, 0..window_height] to NDC in [-1..1]
    Vec2 ndc_coords;
    ndc_coords.x =  (2.0f * x_screen / window_width) - 1.0f;
    ndc_coords.y = -( (2.0f * y_screen / window_height) - 1.0f );
    // Explanation:
    //    x_ndc in [-1..1], left->-1, right->+1
    //    y_ndc in [-1..1], bottom->-1, top->+1
    // We flip the sign on y to match typical OpenGL coordinates 
    // (so y=0 at bottom, y=+1 at top). If you prefer top-left origin, adapt as needed.

    // 2) Scale NDC to your "cage" coordinate system
    //    If your cage spans [-get_cage_half_w()..+get_cage_half_w()] in X
    //    and [-get_cage_half_h()..+get_cage_half_h()] in Y,
    //    multiply each axis by the appropriate half-extent:
    Vec2 cage_coords;
    cage_coords.x = ndc_coords.x * get_cage_half_w();
    cage_coords.y = ndc_coords.y * get_cage_half_h();

    return cage_coords;
}

