#include "MultiComponent.h"
#include "KeysBindings.h"
#include "Box.h"
#include "SearchBox.h"

template<typename T>
MultiComponent<T>::MultiComponent() : Component() {}

template<typename T>
void MultiComponent<T>::next_component() {
    if (selected_ == -1) return;

    if (selected_ + 1 == static_cast<int>(components_.size())) selected_ = 0;
    else if (selected_ + 1 < static_cast<int>(components_.size())) selected_++;
}

template<typename T>
void MultiComponent<T>::previous_component() {
    if (selected_ == -1) return;

    if (selected_ == 0) selected_ = static_cast<int>(components_.size()) - 1;
    else if (selected_ > 0)  selected_--;
}

template<typename T>
void MultiComponent<T>::add_component(T *component) {
    components_.push_back(component);
    selected_ = 0;
}

template<typename T>
void MultiComponent<T>::draw() {
    if (selected_ == -1) return;

    auto comp = dynamic_cast<Component*>(components_.at(selected_));
    comp->draw();
}

template<typename T>
void MultiComponent<T>::handle_input(int ch) {
    switch (ch) {
        case ARROW_LEFT:
            previous_component();
            break;
        case ARROW_RIGHT:
            next_component();
            break;
        default:
            auto comp = dynamic_cast<Component*>(components_.at(selected_));
            comp->handle_input(ch);
    }
}

// Instantiate the template at the end of Box.cpp
template class MultiComponent<Box<TextBox>>;
template class MultiComponent<SearchBox>;
template class MultiComponent<InputLabel>;
