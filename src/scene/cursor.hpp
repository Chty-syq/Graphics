//
// Created by syq on 23-7-10.
//
#pragma once

#include <X11/Xlib.h>
#include <stdexcept>

class CursorManager {
private:
    Display* display;
    Window window;
public:
    CursorManager();
    ~CursorManager();
    void SetCursorPosLinux(int pos_x, int pos_y);
};


CursorManager::CursorManager() {
    this->display = XOpenDisplay(nullptr);
    if (!this->display) {
        throw std::runtime_error("Unexpected Behavior for XOpenDisplay");
    }
    this->window = DefaultRootWindow(display);
}

CursorManager::~CursorManager() {
    XCloseDisplay(display);
}

void CursorManager::SetCursorPosLinux(int pos_x, int pos_y) {
    XWarpPointer(display, None, window, 0, 0, 0, 0, pos_x, pos_y);
    XFlush(display);
}