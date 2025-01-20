#include "TextBox.h"
#include "sstream"
#include "components/KeysBindings.h"
#include "colors/ColorPair.h"
#include "pallets/gruvbox.h"

#include <algorithm>

TextBox::TextBox(int height, int width, int y, int x, bool reversed)
    : Component(height, width, y, x), lines_(std::vector<std::string>()), reversed_(reversed) {
    min_ = 0;
    max_ = height - 2;
}

void TextBox::set_min_(int min) {
    if (min < 0) return;

    min_ = min;
    max_ = std::min(get_height() - 2, min + get_height() - 2);
}

void TextBox::set_max_(int max) {
    if (max > static_cast<int>(lines_.size())) return;

    min_ = std::max(0, max - (get_height() - 2));
    max_ = max;
}

void TextBox::shift_window_up() {
    if (max_ >= static_cast<int>(lines_.size())) return;
    else {
        min_++;
        max_++;
    }
}

void TextBox::shift_window_down() {
    if (min_ <= 0) return;
    else {
        min_--;
        max_--;
    }
}

void TextBox::shift_selected_up() {
    selected_++;
    if (selected_ == max_) shift_window_up();

    if (selected_ == static_cast<int>(lines_.size())) {
        selected_ = 0;

        set_min_(0);
    }
}

void TextBox::shift_selected_down() {
    selected_--;
    if (selected_ == min_ - 1) shift_window_down();

    if (selected_ == -1) {
        selected_ = static_cast<int>(lines_.size()) - 1;

        set_max_(static_cast<int>(lines_.size()));
    }
}

std::vector<std::string> TextBox::get_lines_() {
    return lines_;
}

void TextBox::set_lines_(std::vector<std::string> &lines) {
    bool is_diferent_ = lines.size() != lines_.size();
    lines_ = std::move(lines);

    if (lines_.empty()) select(-1);
    else if (is_diferent_) select(0);
}

void TextBox::set_header_(std::string header) {
    header_ = std::move(header);
}

int TextBox::get_selected() const {
    return selected_;
}

std::string TextBox::get_selected_string() const {
    if (selected_ == -1) return "";

    return lines_.at(selected_);
}

void TextBox::select(int i) {
    if (i < -1 || i >= (int) lines_.size()) return;

    if (i == -1) {
        set_min_(0);
    }
    else {
        set_min_(i);
    }

    selected_ = i;
}

void TextBox::select(std::string &text) {
    // Find the iterator pointing to the element
    auto it = std::find(lines_.begin(), lines_.end(), text);

    // Check if the string was found
    if (it != lines_.end()) {
        // Calculate the index (distance from the beginning)
        selected_ = static_cast<int>(std::distance(lines_.begin(), it));
    }
}

void TextBox::set_highlighted_color(short id) {
    highlighted_color_ = id;
}

void TextBox::remove() {
    if (selected_ == -1) return;

    lines_.erase(lines_.begin() + selected_);

    if (lines_.empty()) select(-1);
    else if (selected_ == lines_.size()) {
        shift_selected_down();
    }
    else {
        max_++;
    }
}

void TextBox::add(std::string string) {
    lines_.push_back(string);
}

void TextBox::draw() {
    //wclear(get_win());

    ColorPair::activate(get_win(), get_box_color());
    box(get_win(), 0, 0);
    if (!header_.empty()) mvwprintw(get_win(), 0, (get_width() - header_.size()) / 2 - 1, "%s", (" " + header_ + " ").c_str());

    int relative_y = (reversed_) ? get_height() - 2 : 1; // starting point based on orientation

    for (int index = min_; index < min_ + get_height() - 2; index++) {
        if (index == selected_) ColorPair::activate(get_win(), highlighted_color_);
        else ColorPair::activate(get_win(), get_color());

        mvwprintw(get_win(), relative_y, 1, "%s", std::string(get_width() - 2, ' ').c_str());

        if (index >= 0 && index < static_cast<int>(lines_.size())) {
            mvwaddch(get_win(), relative_y, 1, ' ');
            mvwprintw(get_win(), relative_y, 2, "%s", lines_.at(index).substr(0, get_width() - 3).c_str());
            mvwaddch(get_win(), relative_y, get_width() - 2, ' ');
        }

        relative_y += (reversed_) ? -1 : 1; // incrementing or decrementing based on orientation
    }

    // refreshwin();
}

void TextBox::handle_input(int ch) {
    if (lines_.empty()) return;

    if (selected_ == -1) { // not selected
        switch (ch) {
            case ARROW_UP:
            case ARROW_DOWN:
                shift_selected_up();
                break;
            default:
                return;
        }
    }
    else { // selected
        switch (ch) {
            case ARROW_UP:
                if (reversed_) shift_selected_up();
                else shift_selected_down();
                break;
            case ARROW_DOWN:
                if (reversed_) shift_selected_down();
                else shift_selected_up();
                break;
            case ENTER:
                on_select_();
                break;
            case ESC:
                on_cancel_();
                selected_ = -1;
            default:
                return;
        }
    }
}

