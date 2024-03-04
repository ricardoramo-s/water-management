#include "TextBox.h"
#include "sstream"
#include "components/KeysBindings.h"
#include "colors/ColorPair.h"
#include "pallets/gruvbox.h"

TextBox::TextBox(int width, int y, int x, std::string& text) : Component(0, width, y, x) {
    std::string current_line;
    std::istringstream iss(text);
    std::string word;
    int current_height = 0;

    while (iss >> word) {
        if (current_line.empty()) {
            current_line += word;
            continue;
        }
        if (current_line.length() + word.length() <= static_cast<size_t>(width) - 2) {
            current_line += " " + word;
        } else {
            // Line is full, add current line and start a new one
            if (current_line.back() == ' ') lines_.push_back(current_line.substr(1)); // Remove leading space
            else lines_.push_back(current_line); // Word is bigger than width
            current_height ++;

            current_line = word; // Start new line with current word
        }
    }

    // Add the last line (or partial line)
    if (!current_line.empty()) {
        lines_.push_back(current_line.substr(1));
    }

    this->resizewin(current_height, width);
}

TextBox::TextBox(int y, int x, std::vector<std::string>& lines) : Component(0, 0, y, x), lines_(std::move(lines)) {
    size_t max_width;

    for (const auto& str : lines_) {
        max_width = std::max(max_width, str.size());
    }

    resizewin(static_cast<int>(lines_.size()), static_cast<int>(max_width));
}

TextBox::TextBox(int height, int width, int y, int x, std::vector<std::string> &lines, bool reversed)
    : Component(height, width, y, x), lines_(lines), reversed_(reversed) {
    min_ = 0;
    max_ = std::min(height, static_cast<int>(lines.size()));
}

void TextBox::draw() {
    short selected_id = ColorPair::get(dark0, light0);
    short default_id = ColorPair::get(light0, dark0);

    int relative_y = (reversed_) ? get_height() - 1 : 0;

    for (int index = min_; index < max_; index++) {
        if (index == selected_) ColorPair::activate(get_win(), selected_id);
        else ColorPair::activate(get_win(), default_id);

        wmove(get_win(), static_cast<int>(relative_y), 0);
        wclrtoeol(get_win());

        mvwaddch(get_win(), static_cast<int>(relative_y), 0, ' ');
        mvwprintw(get_win(), static_cast<int>(relative_y), 1, lines_.at(index).c_str());
        mvwaddch(get_win(), static_cast<int>(relative_y), get_width() - 1, ' ');

        relative_y += (reversed_) ? -1 : 1;
    }

    refreshwin();
}

void TextBox::handle_input() {
    mvprintw(0, 0, ("selected_: " + std::to_string(selected_)).c_str());
    mvprintw(1, 0, ("min_: " + std::to_string(min_)).c_str());
    mvprintw(2, 0, ("max_: " + std::to_string(max_)).c_str());
    refresh();

    int ch = wgetch(get_win());
    mvprintw(3, 0, ("Pressed key: " + std::to_string(ch)).c_str());
    
    if (selected_ == -1) { // not selected
        switch (ch) {
            case ARROW_UP:
            case ARROW_DOWN:
                selected_ = 0;
                set_min_(0);
                break;
            default:
                return;
        }
    }
    else { // selected
        switch (ch) {
            case ARROW_UP:
                selected_ += (reversed_) ? 1 : -1;
                break;
            case ARROW_DOWN:
                selected_ += (reversed_) ? -1 : 1;
                break;
            case ENTER:
                // TODO selecting
                break;
            default:
                return;
        }

        if (selected_ == -1) {
            selected_ = lines_.size() - 1;
            set_max_(lines_.size());
        }
        else if (selected_ == static_cast<int>(lines_.size())) {
            selected_ = 0;
            set_min_(0);
        }
        else if (selected_ == max_) shift_window_up();
        else if (selected_ == min_ - 1) shift_window_down();
    }
}

void TextBox::set_min_(int min) {
    if (min < 0 || min + get_height() > static_cast<int>(lines_.size())) return;

    min_ = min;
    max_ = min + get_height();
}

void TextBox::set_max_(int max) {
    if (max - get_height() < 0 || max > static_cast<int>(lines_.size())) return;

    min_ = max - get_height();
    max_ = max;
}

void TextBox::shift_window_up() {
    if (max_ + 1 > lines_.size()) return;
    else {
        min_++;
        max_++;
    }
}

void TextBox::shift_window_down() {
    if (max_ < 0) return;
    else {
        min_--;
        max_--;
    }
}

