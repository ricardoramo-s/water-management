#ifndef WATER_MANAGEMENT_RESERVOIRMENU_H
#define WATER_MANAGEMENT_RESERVOIRMENU_H

#include "Menu.h"
#include "components/SearchBox.h"
#include "ui/components/MultiComponent.h"

class ReservoirMenu : public Menu {
private:
    SearchBox *search_box_, *connected_box_;
    InputBox *input_box_;

public:
    ReservoirMenu();

    void draw() override;
    void handle_input(int ch);
};


#endif //WATER_MANAGEMENT_RESERVOIRMENU_H
