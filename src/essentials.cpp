#pragma once

#include "../include/essentials.h"

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
