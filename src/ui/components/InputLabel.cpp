#include "InputLabel.h"
#include "KeysBindings.h"
#include "colors/ColorPair.h"
#include "pallets/gruvbox.h"

InputLabel::InputLabel(int width, int y, int x) : Component(1, width, y, x), input_text_(std::string{}), default_text_(std::string{}) {}

InputLabel::InputLabel(int width, int y, int x, std::string default_text) : Component(1, width, y, x), input_text_(std::string{}), default_text_(std::string{default_text}) {}

void InputLabel::draw() {
    ColorPair::apply(get_win(), light0, dark0);
    wclear(get_win());

    if (input_text_.empty()) {
        mvwprintw(get_win(), 0, 0, default_text_.c_str());
    } else {
        if (input_text_.length() <= static_cast<size_t>(get_width()) - 2) {
            mvwprintw(get_win(), 0, 0, "> ");
            wprintw(get_win(), input_text_.c_str());
        }
        else {
            int start = static_cast<int>(get_width()) - 2 + ((input_text_.size() - (get_width() - 1)) / get_width()) * get_width();
            mvwprintw(get_win(), 0, 0, input_text_.substr(start, get_width()).c_str());
        }
    }

    refreshwin();
}

void InputLabel::handle_input() {
    if (input_flag_) {
        input_flag_ = false;
        wmove(get_win(), 0, 0);
    }

    keypad(get_win(), true);
    int ch = wgetch(get_win());

    switch (ch) {
        case BACKSPACE:
            if (!input_text_.empty()) {
                input_text_.pop_back();
            }
            break;
        case KEY_LEFT:  // Example: Handle left arrow key
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
            break;
            // ... other arrow keys, special keys if needed ...
        default:  // Handle regular characters
            if (isprint(ch)) {
                input_text_ += ch;
            }
    }

    refreshwin();
}

bool InputLabel::get_input_flag() const {
    return  input_flag_;
}