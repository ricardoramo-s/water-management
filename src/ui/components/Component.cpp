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

Component::Component() : x_(0), y_(0), width_(0), height_(0), win_(nullptr), panel_(nullptr) {}

Component::Component(int y, int x) : x_(x), y_(y), width_(0), height_(0), win_(nullptr), panel_(nullptr) {}

Component::~Component() {
    if (win_) {
        delwin(win_);
    }

    if (panel_) {
        del_panel(panel_);
    }
}

void Component::set_color(short id) {
    if (win_) {
        ColorPair::activate(win_, id);
        wbkgd(win_, COLOR_PAIR(id));
    }
    color_id_ = id;
}

short Component::get_color() const {
    return color_id_;
}

void Component::set_box_color(short id) {
    box_color_id = id;
}

short Component::get_box_color() const {
    return box_color_id;
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

void Component::hide() const {
    if (panel_ == nullptr) return;
    hide_panel(panel_);
}

void Component::show() const {
    if (panel_ == nullptr) return;

    show_panel(panel_);
}

void Component::highlight() const {
    on_highlight_();
}

void Component::to_back() const {
    if (panel_ == nullptr) return;

    bottom_panel(panel_);
}

void Component::to_front() const {
    if (panel_ == nullptr) return;

    top_panel(panel_);
}

void Component::set_userptr(const void* ptr) const {
    if (panel_ == nullptr) return;

    set_panel_userptr(panel_, ptr);
}

const void *Component::get_userptr() const {
    if (panel_ == nullptr) return nullptr;

    return panel_userptr(panel_);
}

void Component::set_next_component(Component *component) {
    next_component_ = component;
}

Component *Component::get_next_component() const {
    return next_component_;
}

void Component::on_cancel(std::function<void()> callback_function) {
    on_cancel_ = std::move(callback_function);
}

void Component::on_select(std::function<void()> callback_function) {
    on_select_ = std::move(callback_function);
}

void Component::on_highlight(std::function<void()> callback_function) {
    on_highlight_ = std::move(callback_function);
}

void Component::on_select() const {
    on_select_();
}

void Component::on_highlight() const {
    on_highlight_();
}