#ifndef WATER_MANAGEMENT_INPUTLABEL_H
#define WATER_MANAGEMENT_INPUTLABEL_H


#include "Component.h"
#include "string"

class InputLabel : public Component {
private:
    std::string input_text_;
    std::string default_text_;

    bool input_flag_ = true;

public:
    InputLabel(int width, int y, int x);
    InputLabel(int width, int y, int x, std::string default_text);

    void draw() override;
    void handle_input() override;

    bool get_input_flag() const;

};


#endif //WATER_MANAGEMENT_INPUTLABEL_H
