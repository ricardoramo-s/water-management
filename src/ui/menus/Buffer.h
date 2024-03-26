#ifndef WATER_MANAGEMENT_BUFFER_H
#define WATER_MANAGEMENT_BUFFER_H

#include "vector"
#include "unordered_map"
#include "string"
#include "components/Component.h"
#include "components/Cmdline.h"

class Cmdline;

class Buffer : public Component {
protected:
    Cmdline* cmdline_;

    std::unordered_map<std::string, std::function<void()>> commands_ = std::unordered_map<std::string, std::function<void()>>();
    Component *currently_selected_component_ = nullptr, *previously_selected_component_ = nullptr;

public:
    explicit Buffer(Cmdline* cmdline);
    Buffer(int height, int width, int y, int x, Cmdline* cmdline);

    void select_component(Component* component);
    void swap_selected_component();
    void select_previous_component();

    bool call_command(std::string command);
    void add_command(std::string command, std::function<void()> function);
};


#endif //WATER_MANAGEMENT_BUFFER_H
