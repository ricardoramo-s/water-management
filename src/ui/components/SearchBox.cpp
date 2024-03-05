#include "SearchBox.h"
#include "KeysBindings.h"

SearchBox::SearchBox(int height, int width, int y, int x, std::vector<std::string> &options) : Component(y, x) {
    options_ = std::move(options);
    matches_ = std::vector<std::string>();


    auto search_bar = new InputLabel(width, y + height - 2, x, "> ");
    search_bar_ = new Box<InputLabel>(search_bar, "Search");

    auto search_text = new TextBox(height - 4, width, y, x, options_, false);
    search_text_ = new Box<TextBox>(search_text, "Results");
}

void SearchBox::draw() {
    search_text_->draw();
    search_bar_->draw();
}

// Function to convert a string to lowercase
std::string toLowercase(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Function for the case-insensitive search
std::vector<std::string> findMatchingStrings(const std::vector<std::string>& data, const std::string& searchTerm) {
    std::vector<std::string> results;
    std::string lowercaseSearch = toLowercase(searchTerm);

    for (const std::string& str : data) {
        if (toLowercase(str).find(lowercaseSearch) != std::string::npos) {
            results.push_back(str);
        }
    }
    return results;
}

void SearchBox::handle_input(int ch) {
    switch (ch) {
        case ESC:
        case ARROW_UP:
        case ARROW_DOWN:
            search_text_->get_component()->handle_input(ch);
            break;
        default:
            search_bar_->get_component()->handle_input(ch);

            auto lines = findMatchingStrings(options_, search_bar_->get_component()->get_input_text());
            search_text_->get_component()->set_lines_(lines);
            break;
    }
}
