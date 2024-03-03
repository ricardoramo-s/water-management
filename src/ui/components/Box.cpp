#include "Box.h"
#include "TextLabel.h"
#include "InputLabel.h"
#include "colors/ColorPair.h"
#include "pallets/gruvbox.h"

template<typename T>
Box<T>::Box(T *component) : Component(), component_(component), header_(std::string()) {
    auto comp = dynamic_cast<Component*>(component);

    movewin(comp->get_y(), comp->get_x());
    resizewin(comp->get_height(), comp->get_width());
}

template<typename T>
Box<T>::Box(T *component, std::string header) : Component(), component_(component), header_(header) {
    auto comp = dynamic_cast<Component*>(component);

    movewin(comp->get_y(), comp->get_x());
    resizewin(comp->get_height(), comp->get_width());
}

template<typename T>
T *Box<T>::get_component() {
    return component_;
}

template<typename T>
void Box<T>::set_header(std::string header) {
    header_ = std::move(header);
}


template<typename T>
void Box<T>::draw() {
    auto component = dynamic_cast<Component*>(component_);

    if (this->get_x() != component->get_x() - 1 || this->get_y() != component->get_y() - 1) {
        movewin(component->get_y() - 1, component->get_x() - 1);
    }
    if (get_width() != component->get_width() + 2 || get_height() != component->get_height() + 2) {
        resizewin(component->get_height() + 2, component->get_width() + 2);
    }

    ColorPair::apply(get_win(), light0, dark0);
    box(get_win(), 0, 0);

    if (!header_.empty()) mvwprintw(get_win(), 0, (get_width() - header_.size()) / 2 - 1, (" " + header_ + " ").c_str());

    refreshwin();
    component->draw();
}

template<typename T>
void Box<T>::handle_input() {
    auto component = dynamic_cast<Component*>(component_);
    component->handle_input();
}

template<typename T>
Box<T>::~Box() {
    delete component_;
}

template<typename T>
void Box<T>::move_with_component(int y, int x) {
    auto component = dynamic_cast<Component*>(component_);

    component->movewin(y, x);
    movewin(y, x);
}

template<typename T>
void Box<T>::resize_with_component(int height, int width) {
    auto component = dynamic_cast<Component*>(component_);

    component->resizewin(height, width);
    resizewin(height, width);
}

// Instantiate the template at the end of Box.cpp
template class Box<TextBox>;
template class Box<TextLabel>;
template class Box<InputLabel>;