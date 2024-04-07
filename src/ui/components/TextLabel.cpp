#include "TextLabel.h"
#include "colors/ColorPair.h"
#include "components/KeysBindings.h"
#include "pallets/gruvbox.h"

TextLabel::TextLabel(int y, int x, std::string text) : Component(1, static_cast<int>(text.length()), y, x), text_(text) {}
TextLabel::TextLabel(int width, int y, int x) : Component(1, width, y, x), text_({}) {}

void TextLabel::draw() {
    ColorPair::activate(get_win(), get_color());

    mvwprintw(get_win(), 0, 0, "%s", std::string(get_width(), ' ').c_str());
    mvwprintw(get_win(), 0, 0, "%s", text_.c_str());
    refreshwin();
}

void TextLabel::set_text(std::string text) {
    text_ = std::move(text);
}

void TextLabel::handle_input(int ch) {
    switch (ch) {
        case ENTER:
            on_select_();
            break;
        case ESC:
            on_cancel_();
            break;
    }
}