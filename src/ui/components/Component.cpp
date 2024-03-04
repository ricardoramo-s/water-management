#include "Component.h"

int Component::get_height() const {
    return  height_;
}

int Component::get_width() const {
    return width_;
}

int Component::get_x() const {
    return x_;
}

int Component::get_y() const {
    return y_;
}

Component::Component(int height, int width, int y, int x) {
    x_ = x;
    y_ = y;
    height_ = height;
    width_ = width;

    win_ = newwin(height, width, y, x);
    keypad(win_, true);
}

Component::Component() : x_(0), y_(0), width_(0), height_(0), win_(newwin(0, 0, 0, 0)) {}

Component::~Component() {
    delwin(win_);
}

void Component::movewin(int y, int x) {
    mvwin(win_, y, x);

    y_ = y;
    x_ = x;
}

void Component::resizewin(int height, int width) {
    wresize(win_, height, width);

    width_ = width;
    height_ = height;
}

WINDOW *Component::get_win() const {
    return win_;
}

void Component::refreshwin() const {
    wnoutrefresh(win_);
}
