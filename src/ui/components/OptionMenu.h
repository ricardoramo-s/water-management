//
// Created by Ricardo Ramos on 05/03/2024.
//

#ifndef WATER_MANAGEMENT_OPTIONMENU_H
#define WATER_MANAGEMENT_OPTIONMENU_H


#include "Component.h"
#include "TextLabel.h"
#include "vector"

class OptionMenu : public Component {
private:
    std::vector<TextLabel*> options_;

    int selected_ = -1;

    void shift_selected_up();
    void shift_selected_down();

public:
    OptionMenu(int y, int x, std::vector<TextLabel*>& options);
    OptionMenu(int y, int x);

    void add_option(TextLabel* option);
    void add_option(int y, std::string text);

    void draw() override;
    void handle_input() override;
};


#endif //WATER_MANAGEMENT_OPTIONMENU_H
