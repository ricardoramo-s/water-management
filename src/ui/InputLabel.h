#ifndef WATER_MANAGEMENT_INPUTLABEL_H
#define WATER_MANAGEMENT_INPUTLABEL_H


#include "Component.h"
#include "string"

class InputLabel : public Component {
private:
    std::string _input_text;
    std::string _default_text;

    int current_x = 0;
    int current_y = 0;

    bool _input_flag = true;

public:
    InputLabel(int width, int y, int x);
    InputLabel(int width, int y, int x, std::string default_text);

    void draw() override;
    void handle_input() override;

    bool get_input_flag() const;

};


#endif //WATER_MANAGEMENT_INPUTLABEL_H