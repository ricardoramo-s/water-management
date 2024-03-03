#ifndef WATER_MANAGEMENT_TEXTLABEL_H
#define WATER_MANAGEMENT_TEXTLABEL_H


#include "Component.h"
#include "string"

class TextLabel : public Component {
private:
    std::string text_;

public:
    TextLabel(int y, int x, std::string text);

    void draw() override;
    void handle_input() override;

    ~TextLabel();
};


#endif //WATER_MANAGEMENT_TEXTLABEL_H
