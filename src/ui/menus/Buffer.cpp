#include "Buffer.h"
#include "ncurses.h"
#include "colors/ColorPair.h"
#include "pallets/gruvbox.h"

Buffer::Buffer(Cmdline* cmdline) : Component(getmaxy(stdscr), getmaxx(stdscr), 0, 0), cmdline_(cmdline) {}

Buffer::Buffer(int height, int width, int y, int x, Cmdline* cmdline) : Component(height, width, y, x), cmdline_(cmdline) {}

bool Buffer::call_command(std::string command) {
    auto it = commands_.find(command);

    if (it != commands_.end()) {
        it->second();
        return true;
    }
    else {
        return false;
    }
}

void Buffer::add_command(std::string command, std::function<void()> function) {
    commands_.emplace(command, std::move(function));
}

void Buffer::select_component(Component* component) {
    previously_selected_component_ = currently_selected_component_;
    currently_selected_component_ = component;
}

void Buffer::swap_selected_component() {
    std::swap(currently_selected_component_, previously_selected_component_);
}

void Buffer::select_previous_component() {
    currently_selected_component_ = previously_selected_component_;
}