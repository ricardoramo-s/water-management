#include "Box.h"
#include "TextLabel.h"
#include "InputLabel.h"

template<typename T>
Box<T>::Box(T *component) : _component(component), Component() {
    auto comp = dynamic_cast<Component*>(component);

    movewin(comp->get_y(), comp->get_x());
    resizewin(comp->get_height(), comp->get_width());
}

template<typename T>
T *Box<T>::get_component() {
    return _component;
}

template<typename T>
void Box<T>::draw() {
    auto component = dynamic_cast<Component*>(_component);

    if (this->get_x() != component->get_x() - 1 || this->get_y() != component->get_y() - 1) {
        movewin(component->get_y() - 1, component->get_x() - 1);
    }
    if (get_width() != component->get_width() + 2 || get_height() != component->get_height() + 2) {
        resizewin(component->get_height() + 2, component->get_width() + 2);
    }

    box(get_win(), 0, 0);
    wrefresh(get_win());
    component->draw();
}

template<typename T>
void Box<T>::handle_input() {
    auto component = dynamic_cast<Component*>(_component);
    component->handle_input();
}

template<typename T>
Box<T>::~Box() {
    delete _component;
}

template<typename T>
void Box<T>::move_with_component(int y, int x) {
    auto component = dynamic_cast<Component*>(_component);

    component->movewin(y, x);
    movewin(y, x);
}

template<typename T>
void Box<T>::resize_with_component(int height, int width) {
    auto component = dynamic_cast<Component*>(_component);

    component->resizewin(height, width);
    resizewin(height, width);
}

// Instantiate the template at the end of Box.cpp
template class Box<TextBox>;
template class Box<TextLabel>;
template class Box<InputLabel>;