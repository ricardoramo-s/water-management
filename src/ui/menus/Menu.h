#ifndef WATER_MANAGEMENT_MENU_H
#define WATER_MANAGEMENT_MENU_H

#include "vector"
#include "components/Component.h"

class Menu {
protected:
    int height_, width_;

public:
    Menu();

    virtual void draw() = 0;
};


#endif //WATER_MANAGEMENT_MENU_H
