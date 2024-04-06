//
// Created by Ricardo Ramos on 05/03/2024.
//

#include "OptionMenu.h"
#include "KeysBindings.h"
#include "pallets/gruvbox.h"

OptionMenu::OptionMenu(int y, int x, std::vector<TextLabel *> &options) : Component(0,0,0,0), options_(std::move(options)) {}

OptionMenu::OptionMenu(int y, int x) : Component(0,0,0,0), options_(std::vector<TextLabel*>()) {}

OptionMenu::OptionMenu() : Component(), options_(std::vector<TextLabel*>()) {}

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

void OptionMenu::select(int i) {
    if (i < -1 || i >= (int) options_.size()) return;

    selected_ = i;
}

void OptionMenu::draw() {
    for (int i = 0; i < (int) options_.size(); i++) {
        if (i == selected_) {
            options_.at(i)->set_color(ColorPair::get(dark0, light0));
        }
        else {
            options_.at(i)->set_color(ColorPair::get(light0, dark0));
        }

        options_.at(i)->draw();
    }
}

void OptionMenu::handle_input(int ch) {
    switch (ch) {
        case ESC:
            selected_ = -1;
            break;
        case ENTER:
            options_.at(selected_)->on_select();
            break;
        case ARROW_UP:
            shift_selected_up();
            break;
        case ARROW_DOWN:
            shift_selected_down();
            break;
    }
}

void OptionMenu::hide() const {
    for (auto option : options_) {
        option->hide();
    }
}

void OptionMenu::show() const {
    for (auto option : options_) {
        option->show();
    }
}

OptionMenu::~OptionMenu() {
    for (auto option : options_) {
        delete option;
    }
}
