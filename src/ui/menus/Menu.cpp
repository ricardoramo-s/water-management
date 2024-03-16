#include "Menu.h"
#include "ncurses.h"
#include "colors/ColorPair.h"
#include "pallets/gruvbox.h"

Menu::Menu(Cmdline* cmdline) : Component(getmaxy(stdscr), getmaxx(stdscr), 0, 0), cmdline_(cmdline) {}

Menu::Menu(int height, int width, int y, int x, Cmdline* cmdline) : Component(height, width, y, x), cmdline_(cmdline) {}

bool Menu::call_command(std::string command) {
    auto it = commands_.find(command);

    if (it != commands_.end()) {
        it->second();
        return true;
    }
    else {
        return false;
    }
}

void Menu::add_command(std::string command, std::function<void()> function) {
    commands_.emplace(command, std::move(function));
}

void Menu::select_component(Component* component) {
    previously_selected_component_ = currently_selected_component_;
    currently_selected_component_ = component;
}

void Menu::swap_selected_component() {
    std::swap(currently_selected_component_, previously_selected_component_);
}

void Menu::select_previous_component() {
    currently_selected_component_ = previously_selected_component_;
}