#include "InputLabel.h"
#include "KeysBindings.h"
#include "colors/ColorPair.h"
#include "pallets/gruvbox.h"

InputLabel::InputLabel(int width, int y, int x) : Component(1, width, y, x), _input_text(std::string{}), _default_text(std::string{}) {}

InputLabel::InputLabel(int width, int y, int x, std::string default_text) : Component(1, width, y, x), _input_text(std::string{}), _default_text(std::string{default_text}) {}

void InputLabel::draw() {
    ColorPair::apply(get_win(), light0, dark0);
    wclear(get_win());

    if (_input_text.empty()) {
        mvwprintw(get_win(), 0, 0, _default_text.c_str());
    } else {
        if (_input_text.length() <= static_cast<size_t>(get_width()) - 2) {
            mvwprintw(get_win(), 0, 0, "> ");
            wprintw(get_win(), _input_text.c_str());
        }
        else {
            int start = static_cast<int>(get_width()) - 2 + ((_input_text.size() - (get_width() - 1)) / get_width()) * get_width();
            mvwprintw(get_win(), 0, 0, _input_text.substr(start, get_width()).c_str());
        }
    }

    refreshwin();
}

void InputLabel::handle_input() {
    if (_input_flag) {
        _input_flag = false;
        wmove(get_win(), 0, 0);
    }

    keypad(get_win(), true);
    int ch = wgetch(get_win());

    switch (ch) {
        case BACKSPACE:  // Handle backspace (assuming 127 is the correct code)
            if (!_input_text.empty()) {
                _input_text.pop_back();
            }
            break;
        case KEY_LEFT:  // Example: Handle left arrow key
            // ... TODO Implement left arrow handling ...
            break;
        case KEY_RIGHT:
            // ... TODO Implement right arrow handling ...
            break;
        case CTRL_U:
            _input_text.clear();
            break;
        case ENTER:
            _input_flag = true;
            break;
            // ... other arrow keys, special keys if needed ...
        default:  // Handle regular characters
            if (isprint(ch)) {
                _input_text += ch;
            }
    }

    refreshwin();
}

bool InputLabel::get_input_flag() const {
    return  _input_flag;
}