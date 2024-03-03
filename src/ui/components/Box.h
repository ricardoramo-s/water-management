#ifndef WATER_MANAGEMENT_BOX_H
#define WATER_MANAGEMENT_BOX_H


#include <type_traits>
#include "Component.h"
#include "TextBox.h"

template <typename T>
class Box : public Component {
    static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");

private:
    T* _component;
    std::string _header;

public:
    explicit Box(T* component);
    Box(T* component, std::string header);

    T* get_component();
    void set_header(std::string header);

    void draw() override;
    void handle_input() override;

    void move_with_component(int y, int x);
    void resize_with_component(int height, int width);

    ~Box();
};


#endif //WATER_MANAGEMENT_BOX_H
