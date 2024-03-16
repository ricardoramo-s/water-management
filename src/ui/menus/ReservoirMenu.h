#ifndef WATER_MANAGEMENT_RESERVOIRMENU_H
#define WATER_MANAGEMENT_RESERVOIRMENU_H

#include "Menu.h"
#include "components/SearchBox.h"
#include "components/Cmdline.h"
#include "ui/components/MultiComponent.h"

class ReservoirMenu : public Menu {
private:
    SearchBox *search_box_, *connected_box_;

public:
    explicit ReservoirMenu(Cmdline* cmdline);

    void draw() override;
    void handle_input(int ch) override;
};


#endif //WATER_MANAGEMENT_RESERVOIRMENU_H
