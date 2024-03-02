#include "TextBox.h"
#include "sstream"

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
        if (current_line.length() + word.length() <= static_cast<size_t>(width)) {
            current_line += " " + word;
        } else {
            // Line is full, add current line and start a new one
            if (current_line.back() == ' ') _lines.push_back(current_line.substr(1)); // Remove leading space
            else _lines.push_back(current_line); // Word is bigger than width
            current_height ++;

            current_line = word; // Start new line with current word
        }
    }

    // Add the last line (or partial line)
    if (!current_line.empty()) {
        _lines.push_back(current_line.substr(1));
    }

    this->resizewin(current_height, width);
}

TextBox::TextBox(int y, int x, std::vector<std::string>& lines) : Component(0, 0, y, x), _lines(std::move(lines)) {
    size_t max_width;

    for (const auto& str : _lines) {
        max_width = std::max(max_width, str.size());
    }

    resizewin(static_cast<int>(_lines.size()), static_cast<int>(max_width));
}

void TextBox::draw() {
    for (size_t y = 0; y < _lines.size(); y++) {
        mvwprintw(get_win(), static_cast<int>(y), 0, _lines.at(y).c_str());
    }

    refreshwin();
}

void TextBox::handle_input() {
    // TODO
}


