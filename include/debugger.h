#pragma once

class Debugger {
public:
    virtual void draw_debug_info() = 0;
    virtual ~Debugger() = default;
};
