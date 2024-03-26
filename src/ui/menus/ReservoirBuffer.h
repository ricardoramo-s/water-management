#ifndef WATER_MANAGEMENT_RESERVOIRBUFFER_H
#define WATER_MANAGEMENT_RESERVOIRBUFFER_H

#include "Buffer.h"
#include "components/SearchBox.h"
#include "components/Cmdline.h"
#include "ui/components/MultiComponent.h"

class ReservoirBuffer : public Buffer {
private:
    SearchBox *search_box_, *connected_box_;

public:
    explicit ReservoirBuffer(Cmdline* cmdline);

    void draw() override;
    void handle_input(int ch) override;
};


#endif //WATER_MANAGEMENT_RESERVOIRBUFFER_H
