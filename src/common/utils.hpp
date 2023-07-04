//
// Created by syq on 23-7-4.
//
#pragma once

#include <X11/Xlib.h>
#include <stdexcept>

namespace utils {

    void SetCursorPosLinux(int pos_x, int pos_y) {
        auto display = XOpenDisplay(nullptr);
        if(!display) {
            throw std::runtime_error("Unexpected Behavior for SetCursorPosLinux()");
        }
        auto window = DefaultRootWindow(display);
        XWarpPointer(display, None, window, 0, 0, 0, 0, pos_x, pos_y);
        XFlush(display);
        XCloseDisplay(display);
    }

}