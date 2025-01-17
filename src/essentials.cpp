#pragma once

#include "../include/essentials.h"

std::ostream& operator<<(std::ostream& os, CageSide side) {
    switch (side) {
        case C_S_TOP: os << "TOP"; break;
        case C_S_BOTTOM: os << "BOTTOM"; break;
        case C_S_RIGHT: os << "RIGHT"; break;
        case C_S_LEFT: os << "LEFT"; break;
        default: os << "UNKNOWN"; break;
    }
    return os;
}
