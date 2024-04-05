#include "InputBox.h"

#include <utility>
#include "ncurses.h"
#include "KeysBindings.h"
#include "colors/ColorPair.h"
#include "pallets/gruvbox.h"

InputBox::InputBox(int width, int y, int x, std::string default_text) : Component(3, width, y, x), input_text_(std::string{}), default_text_(std::string{std::move(default_text)}) {}

InputBox::InputBox(int width, int y, int x, std::string default_text, std::string header, short text_color_id,
                   short box_color_id, std::function<void()> on_select, std::function<void()> on_cancel) : Component(3, width, y, x) {
    default_text_ = std::move(default_text);
    header_ = std::move(header);
    set_color(text_color_id);
    on_select_ = std::move(on_select);
    on_cancel_ = std::move(on_cancel);
}

void InputBox::draw() {
    ColorPair::activate(get_win(), get_box_color());
    wclear(get_win());
    box(get_win(), 0, 0);
    if (!header_.empty()) mvwprintw(get_win(), 0, (get_width() - static_cast<int>(header_.size())) / 2 - 1, "%s", (" " + header_ + " ").c_str());

    ColorPair::activate(get_win(), get_color());
    int actual_width = get_width() - 2;

    if (input_text_.empty()) {
        mvwprintw(get_win(), 1, 1, "%s", default_text_.c_str());
    } else {
        if (input_text_.length() <= static_cast<size_t>(get_width()) - 4) {
            mvwprintw(get_win(), 1, 1, "❯ ");
            wprintw(get_win(), "%s", input_text_.c_str());
        }
        else {
            // substring calculation algorithm
            int start = actual_width - 2 +
                    ((static_cast<int>(input_text_.size()) - (actual_width - 1)) / actual_width) * actual_width;
            mvwprintw(get_win(), 1, 1, "%s", input_text_.substr(start, get_width() - 1).c_str());
        }
    }

    refreshwin();
}

void InputBox::handle_input(int ch) {
    input_flag_ = false;

    switch (ch) {
        case BACKSPACE:
            if (!input_text_.empty()) {
                input_text_.pop_back();
                input_flag_ = true;
            }
            break;
        case ESC:
            on_cancel_();
            break;
        case CTRL_U:
            clear();
            break;
        case ENTER:
            on_select_();
            break;
        default:  // Handle regular characters
            if (isprint(ch)) {
                input_text_ += ch;
                input_flag_ = true;
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

void InputBox::clear() {
    input_text_.clear();
}

void InputBox::on_select(std::function<void()> callback_function) {
    on_select_ = std::move(callback_function);
}

void InputBox::on_cancel(std::function<void()> callback_function) {
    on_cancel_ = std::move(callback_function);
}
