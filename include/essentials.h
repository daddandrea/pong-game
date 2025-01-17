#pragma once

#include <ostream>
#define MARGIN 0.1f

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
