//
// Created by Ricardo Ramos on 05/03/2024.
//

#include "ReservoirMenu.h"

ReservoirMenu::ReservoirMenu() {
    multiTextBox = new MultiComponent<Box<TextBox>>();
    auto text_box1 = new TextBox(height_ / 4 - 1, (width_ / 2) - 3, height_ - height_ / 4, width_ / 2 + 2, false);
    auto text_box2 = new TextBox(height_ / 4 - 1, (width_ / 2) - 3, height_ - height_ / 4, width_ / 2 + 2, false);
    multiTextBox->add_component(new Box<TextBox>(text_box1, "Connected Cities"));
    multiTextBox->add_component(new Box<TextBox>(text_box2, "Connected Reservoir"));
}

void ReservoirMenu::draw() {
    multiTextBox->draw();
}

void ReservoirMenu::handle_input(int ch) {
    multiTextBox->handle_input(ch);
}