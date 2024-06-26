#include "MultiComponent.h"
#include "ui/components/KeysBindings.h"
#include "SearchBox.h"

template<typename T>
MultiComponent<T>::MultiComponent() : Component() {}

template<typename T>
void MultiComponent<T>::next_component() {
    if (selected_ == -1 || components_.size() == 1) return;

    dynamic_cast<Component*>(components_.at(selected_))->hide();
    if (selected_ + 1 == static_cast<int>(components_.size())) selected_ = 0;
    else if (selected_ + 1 < static_cast<int>(components_.size())) selected_++;
}

template<typename T>
void MultiComponent<T>::previous_component() {
    if (selected_ == -1 || components_.size() == 1) return;

    dynamic_cast<Component*>(components_.at(selected_))->hide();
    if (selected_ == 0) selected_ = static_cast<int>(components_.size()) - 1;
    else if (selected_ > 0)  selected_--;
}

template<typename T>
void MultiComponent<T>::add_component(T *component) {
    components_.push_back(component);
    selected_ = 0;
}

template<typename T>
int MultiComponent<T>::get_selected() const {
    return selected_;
}

template<typename T>
T *MultiComponent<T>::get_selected_component() const {
    if (selected_ == -1) return nullptr;
    else return components_.at(selected_);
}

template<typename T>
T *MultiComponent<T>::get_component(int i) const {
    if (i < 0 || i >= components_.size()) return nullptr;
    else return components_.at(i);
}

template<typename T>
void MultiComponent<T>::draw() {
    if (selected_ == -1) return;

    auto comp = dynamic_cast<Component*>(components_.at(selected_));
    comp->set_color(get_color());
    comp->show();
    comp->draw();
}

template<typename T>
void MultiComponent<T>::handle_input(int ch) {
    if (components_.empty()) return;
    else if (selected_ == -1) selected_ = 0;

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

template<typename T>
void MultiComponent<T>::hide() const {
    for (auto component : components_) {
        Component* pComponent = dynamic_cast<Component*>(component);
        pComponent->hide();
    }

    hide_panel(get_panel());
}

template<typename T>
void MultiComponent<T>::show() const {
    show_panel(get_panel());

    for (auto component : components_) {
        Component* pComponent = dynamic_cast<Component*>(component);
        pComponent->show();
    }
}

template<typename T>
MultiComponent<T>::~MultiComponent() {
    for (auto component : components_) {
        delete component;
    }
}

// Instantiate the template at the end of Box.cpp
template class MultiComponent<TextBox>;
