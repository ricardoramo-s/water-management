#include "TextBox.h"
#include "sstream"
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
    selected_ = 1;
}

void TextBox::draw() {
    min_ = std::max(min_, 0);
    max_ = std::min({max_, get_width(), static_cast<int>(lines_.size())});

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
    if (selected_ == -1) { // not selected

    }

    getch();
}


