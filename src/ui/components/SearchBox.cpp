#include "SearchBox.h"
#include "KeysBindings.h"
#include "colors/ColorPair.h"
#include "pallets/gruvbox.h"

SearchBox::SearchBox(int height, int width, int y, int x) : Component(height, width, y, x), options_(std::vector<std::vector<std::string>>()) {
    input_box_ = new InputBox(width, y + height - 3, x, "❯ ");
    input_box_->set_header_("Search");

    multi_text_box_ = new MultiComponent<TextBox>();
}

void SearchBox::add_options(std::vector<std::string> &options, std::string header) {
    auto search_text = new TextBox(get_height() - 3, get_width(), get_y(), get_x(), true);
    search_text->set_header_(std::move(header));
    auto options_copy = std::vector<std::string>(options);

    search_text->set_lines_(options_copy);

    multi_text_box_->add_component(search_text);
    options_.push_back(std::move(options));
}

void SearchBox::draw() {
    ColorPair::apply(get_win(), light0, dark0);

    multi_text_box_->draw();
    input_box_->draw();
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
    bool request_update = false;

    switch (ch) {
        case ARROW_LEFT:
        case ARROW_RIGHT:
            request_update = true;
        case ESC:
        case ARROW_UP:
        case ARROW_DOWN:
            multi_text_box_->handle_input(ch);
            break;
        default:
            input_box_->handle_input(ch);
            request_update = true;
            break;
    }

    if (multi_text_box_->get_selected() != -1 && request_update) {
        auto lines = findMatchingStrings(options_.at(multi_text_box_->get_selected()),
                                         input_box_->get_input_text());
        multi_text_box_->get_selected_component()->set_lines_(lines);
    }
}


