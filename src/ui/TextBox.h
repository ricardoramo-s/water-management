#ifndef WATER_MANAGEMENT_TEXTBOX_H
#define WATER_MANAGEMENT_TEXTBOX_H

#include "Component.h"
#include "string"

class TextBox : public Component {
private:
    std::vector<std::string> _lines;

public:
    TextBox(int width, int y, int x, std::string& text);
    TextBox(int y, int x, std::vector<std::string>& lines);


    void draw() override;
    void handle_input() override;
};


#endif //WATER_MANAGEMENT_TEXTBOX_H
