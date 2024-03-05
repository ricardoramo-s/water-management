#ifndef WATER_MANAGEMENT_SEARCHBOX_H
#define WATER_MANAGEMENT_SEARCHBOX_H

#include "TextBox.h"
#include "InputLabel.h"
#include "Box.h"
#include "vector"

class SearchBox : public Component {
    Box<TextBox>* search_text_;
    Box<InputLabel>* search_bar_;
    std::vector<std::string> options_;
    std::vector<std::string> matches_;

public:
    SearchBox(int height, int width, int y, int x);

    void draw() override;
    void handle_input(int ch) override;

};


#endif //WATER_MANAGEMENT_SEARCHBOX_H
