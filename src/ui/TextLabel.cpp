//
// Created by Ricardo Ramos on 02/03/2024.
//

#include "TextLabel.h"

TextLabel::TextLabel(int y, int x, std::string text) : _text(text), Component(1, static_cast<int>(text.length()), y, x) {}

TextLabel::~TextLabel() = default;

void TextLabel::draw() {
    mvwprintw(get_win(), 0, 0, _text.c_str());

    refreshwin();
}

void TextLabel::handle_input() {

}