#ifndef WATER_MANAGEMENT_SEARCHBOX_H
#define WATER_MANAGEMENT_SEARCHBOX_H

#include "TextBox.h"
#include "InputBox.h"
#include "Box.h"
#include "vector"
#include "components/MultiComponent.h"

class SearchBox : public Component {
    MultiComponent<TextBox>* multi_text_box_;
    InputBox* input_box_;

    std::vector<std::vector<std::string>> options_;
public:
    SearchBox(int height, int width, int y, int x);

    void add_options(std::vector<std::string>& options, std::string header);

    void draw() override;
    void handle_input(int ch) override;

};


#endif //WATER_MANAGEMENT_SEARCHBOX_H
