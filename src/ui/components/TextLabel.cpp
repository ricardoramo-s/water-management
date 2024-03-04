#include "TextLabel.h"
#include "colors/ColorPair.h"
#include "pallets/gruvbox.h"

TextLabel::TextLabel(int y, int x, std::string text) : Component(1, static_cast<int>(text.length()), y, x), text_(text) {}

TextLabel::~TextLabel() = default;

void TextLabel::draw() {
    ColorPair::apply(get_win(), light0, dark0);

    mvwprintw(get_win(), 0, 0, text_.c_str());
    refreshwin();
}

void TextLabel::handle_input() {

}