#include "InputBox.h"

#include <utility>
#include "KeysBindings.h"
#include "colors/ColorPair.h"
#include "pallets/gruvbox.h"

InputBox::InputBox(int width, int y, int x) : Component(3, width, y, x), input_text_(std::string{}), default_text_(std::string{}) {}

InputBox::InputBox(int width, int y, int x, std::string default_text) : Component(3, width, y, x), input_text_(std::string{}), default_text_(std::string{std::move(default_text)}) {}

void InputBox::draw() {
    ColorPair::apply(get_win(), light0, dark0);
    wclear(get_win());
    box(get_win(), 0, 0);
    if (!header_.empty()) mvwprintw(get_win(), 0, (get_width() - header_.size()) / 2 - 1, (" " + header_ + " ").c_str());

    int actual_width = get_width() - 2;

    if (input_text_.empty()) {
        mvwprintw(get_win(), 1, 1, default_text_.c_str());
    } else {
        if (input_text_.length() <= static_cast<size_t>(get_width()) - 4) {
            mvwprintw(get_win(), 1, 1, "❯ ");
            wprintw(get_win(), input_text_.c_str());
        }
        else {
            // substring calculation algorithm
            int start = actual_width - 2 +
                    ((static_cast<int>(input_text_.size()) - (actual_width - 1)) / actual_width) * actual_width;
            mvwprintw(get_win(), 1, 1, input_text_.substr(start, get_width() - 1).c_str());
        }
    }

    refreshwin();
}

void InputBox::handle_input(int ch) {
    if (input_flag_) input_flag_ = false;

    switch (ch) {
        case BACKSPACE:
            if (!input_text_.empty()) {
                input_text_.pop_back();
            }
            break;
        case KEY_LEFT:
            // ... TODO Implement left arrow handling ...
            break;
        case KEY_RIGHT:
            // ... TODO Implement right arrow handling ...
            break;
        case CTRL_U:
            input_text_.clear();
            break;
        case ENTER:
            input_flag_ = true;
            // TODO Event handler system ...
            break;
        default:  // Handle regular characters
            if (isprint(ch)) {
                input_text_ += ch;
            }
    }

    refreshwin();
}

bool InputBox::get_input_flag() const {
    return  input_flag_;
}

std::string InputBox::get_input_text() const {
    return input_text_;
}

void InputBox::set_header_(std::string header) {
    header_ = std::move(header);
}
