#pragma once

#include <cmath>
#define FOV_DEGREES 45
#define ASPECT_RATIO 1920.0f / 1080.0f
#define NEAR_CLIPPING_PLANE 1.0f
#define FAR_CLIPPING_PLANE 500.0f
#define Z_INITIAL_TRANSLATE -15.0f
#define CAGE_LINE_WIDTH 2.0f
#define CAGE_HALF_HEIGHT (std::floorf(float(std::abs(Z_INITIAL_TRANSLATE)) * std::tanf((FOV_DEGREES * M_PIf / 180.0f) / 2.0f)))
#define CAGE_HALF_WIDTH std::floorf(CAGE_HALF_HEIGHT * (ASPECT_RATIO))

void render_game();
