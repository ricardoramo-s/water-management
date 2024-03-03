#include "TextLabel.h"
#include "ui/colors/ColorPair.h"
#include "ui/pallets/gruvbox.h"

TextLabel::TextLabel(int y, int x, std::string text) : _text(text), Component(1, static_cast<int>(text.length()), y, x) {}

TextLabel::~TextLabel() = default;

void TextLabel::draw() {
    ColorPair::activate(get_win(), light0, dark0);

    mvwprintw(get_win(), 0, 0, _text.c_str());
    refreshwin();
}

void TextLabel::handle_input() {

}