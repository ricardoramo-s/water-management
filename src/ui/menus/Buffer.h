#ifndef WATER_MANAGEMENT_BUFFER_H
#define WATER_MANAGEMENT_BUFFER_H

#include "vector"
#include "unordered_map"
#include "string"
#include "components/Component.h"

class Cmdline;

class Buffer : public Component {
protected:
    Component *currently_selected_component_ = nullptr, *previously_selected_component_ = nullptr;

    Buffer *next_buffer_ = nullptr, *previous_buffer_ = nullptr;

public:
    Buffer();
    Buffer(int height, int width, int y, int x);

    void select_component(Component* component);
    void swap_selected_component();
    void select_previous_component();

    Buffer* get_next_buffer();
    void previous_buffer(Buffer* buffer);
};


#endif //WATER_MANAGEMENT_BUFFER_H
