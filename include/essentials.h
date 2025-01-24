#pragma once

#include <ostream>
#include <cmath>

#define MARGIN 0.1f
#define FOV_DEGREES 45
#define ASPECT_RATIO 1920.0f / 1080.0f
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define NEAR_CLIPPING_PLANE 1.0f
#define FAR_CLIPPING_PLANE 500.0f
#define Z_INITIAL_TRANSLATE -15.0f
#define CAGE_LINE_WIDTH 2.0f

typedef struct _color {
    float r;
    float g;
    float b;
} Color;

typedef struct _vec2 {
    float x;
    float y;
} Vec2;

enum CageSide { CAGE_SIDE_NONE, CAGE_SIDE_TOP, CAGE_SIDE_BOTTOM, CAGE_SIDE_RIGHT, CAGE_SIDE_LEFT };
std::ostream& operator<<(std::ostream& os, CageSide side);

float get_viewport_half_w();
float get_viewport_half_h();
float get_cage_half_h();
float get_cage_half_w();

Vec2 opengl_to_text_coords(float x_ndc, float y_ndc, int window_width, int window_height);
Vec2 text_to_opengl_coords(float x_screen, float y_screen, int window_width, int window_height);
