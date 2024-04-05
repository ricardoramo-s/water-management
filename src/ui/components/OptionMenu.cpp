//
// Created by Ricardo Ramos on 05/03/2024.
//

#include "OptionMenu.h"
#include "KeysBindings.h"
#include "pallets/gruvbox.h"

OptionMenu::OptionMenu(int y, int x, std::vector<TextLabel *> &options) : Component(y,x), options_(std::move(options)) {}

OptionMenu::OptionMenu(int y, int x) : Component(y,x), options_(std::vector<TextLabel*>()) {}

void OptionMenu::add_option(TextLabel *option) {
    options_.push_back(option);
}

void OptionMenu::add_option(int y, std::string text) {
    options_.push_back(new TextLabel(get_y() + y, get_x(), text));
}

void OptionMenu::shift_selected_up() {
    if (selected_ == -1) return;

    selected_--;
    if (selected_ < 0) selected_ = 0;
}

void OptionMenu::shift_selected_down() {
    selected_++;
    if (selected_ >= static_cast<int>(options_.size())) selected_ = static_cast<int>(options_.size()) - 1;
}

void OptionMenu::draw() {
    for (size_t i = 0; i < options_.size(); i++) {
        if (static_cast<int>(i) == selected_) options_.at(i)->draw(ColorPair::get(dark0, light0));
        else options_.at(i)->draw(ColorPair::get(light0, dark0));
    }
}

void OptionMenu::handle_input(int ch) {
    switch (ch) {
        case ESC:
            selected_ = -1;
            break;
        case ARROW_UP:
            shift_selected_up();
            break;
        case ARROW_DOWN:
            shift_selected_down();
            break;
    }
}

OptionMenu::~OptionMenu() {
    for (auto option : options_) {
        delete option;
    }
}
