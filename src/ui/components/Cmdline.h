//
// Created by Ricardo Ramos on 16/03/2024.
//

#ifndef WATER_MANAGEMENT_CMDLINE_H
#define WATER_MANAGEMENT_CMDLINE_H

#include "InputBox.h"
#include "menus/Buffer.h"

class Buffer;

class Cmdline : public InputBox {
private:
    Buffer* current_menu_ = nullptr;

public:
    Cmdline();

    void set_current_menu(Buffer* menu);
};


#endif //WATER_MANAGEMENT_CMDLINE_H
