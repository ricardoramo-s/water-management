#include "Component.h"
#include "panel.h"
#include "colors/ColorPair.h"

PANEL *Component::get_panel() const {
    return panel_;
}

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
    panel_ = new_panel(win_);

    keypad(win_, true);
}

Component::Component() : x_(0), y_(0), width_(0), height_(0), win_(nullptr) {}

Component::Component(int y, int x) : x_(x), y_(y), width_(0), height_(0), win_(nullptr) {}

Component::~Component() {
    delwin(win_);
}

void Component::set_color(short id) {
    color_id_ = id;
}

short Component::get_color() const {
    return color_id_;
}

void Component::movewin(int y, int x) {
    if (win_ == nullptr) return;

    mvwin(win_, y, x);

    y_ = y;
    x_ = x;
}

void Component::resizewin(int height, int width) {
    if (win_ == nullptr) return;

    wresize(win_, height, width);

    width_ = width;
    height_ = height;
}

WINDOW *Component::get_win() const {
    return win_;
}

void Component::refreshwin() const {
    if (win_ == nullptr) return;

    wnoutrefresh(win_);
}
