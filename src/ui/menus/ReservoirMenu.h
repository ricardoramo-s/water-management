//
// Created by Ricardo Ramos on 05/03/2024.
//

#ifndef WATER_MANAGEMENT_RESERVOIRMENU_H
#define WATER_MANAGEMENT_RESERVOIRMENU_H

#include "Menu.h"
#include "components/SearchBox.h"
#include "components/Box.h"
#include "components/MultiComponent.h"

class ReservoirMenu : public Menu {
private:
    SearchBox* searchBox;
    MultiComponent<Box<TextBox>>* multiTextBox;

public:
    ReservoirMenu();

    void draw() override;
    void handle_input(int ch);
};


#endif //WATER_MANAGEMENT_RESERVOIRMENU_H
