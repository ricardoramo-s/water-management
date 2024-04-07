//
// Created by Ricardo Ramos on 05/03/2024.
//

#ifndef WATER_MANAGEMENT_MULTICOMPONENT_H
#define WATER_MANAGEMENT_MULTICOMPONENT_H

#include "ui/components/TextBox.h"

template<typename T>
class MultiComponent : public Component {
    static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");

private:
    std::vector<T*> components_ = std::vector<T*>();
    int selected_ = -1;

    void next_component();
    void previous_component();

public:
    MultiComponent();

    void add_component(T* component);

    int get_selected() const;
    T* get_selected_component() const;
    T* get_component(int i) const;

    void draw() override;
    void handle_input(int ch) override;

    void hide() const override;
    void show() const override;

    ~MultiComponent() override;
};


#endif //WATER_MANAGEMENT_MULTICOMPONENT_H
