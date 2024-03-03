#include "Component.h"
#include "../pallets/gruvbox.h"

int Component::get_height() const {
    return  _height;
}

int Component::get_width() const {
    return _width;
}

int Component::get_x() const {
    return _x;
}

int Component::get_y() const {
    return _y;
}

Component::Component(int height, int width, int y, int x) {
    _x = x;
    _y = y;
    _height = height;
    _width = width;

    _win = newwin(height, width, y, x);
}

Component::Component() : _x(0), _y(0), _width(0), _height(0), _win(newwin(0, 0, 0, 0)) {}

Component::~Component() {
    delwin(_win);
}

void Component::movewin(int y, int x) {
    mvwin(_win, y, x);

    _y = y;
    _x = x;
}

void Component::resizewin(int height, int width) {
    wresize(_win, height, width);

    _width = width;
    _height = height;
}

WINDOW *Component::get_win() const {
    return _win;
}

void Component::refreshwin() const {
    wnoutrefresh(_win);
}
