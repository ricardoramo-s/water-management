#ifndef WATER_MANAGEMENT_SEARCHBOX_H
#define WATER_MANAGEMENT_SEARCHBOX_H

#include "TextBox.h"
#include "InputBox.h"
#include "vector"
#include "components/MultiComponent.h"

class SearchBox : public Component {
    MultiComponent<TextBox>* multi_text_box_;
    InputBox* input_box_;

    std::vector<std::vector<std::string>> options_;
    short box_color_id_ = 0;
    short highlighted_color_id_ = 0;

public:
    SearchBox(int height, int width, int y, int x);

    void add_options(std::vector<std::string>& options, std::string header);
    void set_box_color(short id);
    void set_highlighted_color(short id);

    void draw() override;
    void handle_input(int ch) override;

};


#endif //WATER_MANAGEMENT_SEARCHBOX_H
