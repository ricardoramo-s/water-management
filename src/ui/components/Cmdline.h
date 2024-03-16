//
// Created by Ricardo Ramos on 16/03/2024.
//

#ifndef WATER_MANAGEMENT_CMDLINE_H
#define WATER_MANAGEMENT_CMDLINE_H

#include "InputBox.h"
#include "menus/Menu.h"

class Menu;

class Cmdline : public InputBox {
private:
    Menu* current_menu_ = nullptr;

public:
    Cmdline();

    void set_current_menu(Menu* menu);
};


#endif //WATER_MANAGEMENT_CMDLINE_H
