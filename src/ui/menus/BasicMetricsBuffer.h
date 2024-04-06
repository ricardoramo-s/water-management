#ifndef WATER_MANAGEMENT_BASICMETRICSBUFFER_H
#define WATER_MANAGEMENT_BASICMETRICSBUFFER_H

#include "Buffer.h"
#include "ui/components/SearchBox.h"
#include "components/TextLabel.h"
#include "BalanceBuffer.h"
#include "components/OptionMenu.h"
#include "ExportBuffer.h"
#include "BaseClasses/City.h"


class BasicMetricsBuffer : public Buffer {
private:
    SearchBox *search_box_;
    TextLabel *max_flow_;
    TextLabel *id_, *code_, *demand_, *flow_, *deficit_, *population_;
    TextLabel *balance_, *export_;

    BalanceBuffer *balance_buffer_;
    ExportBuffer *export_buffer_;

    void read_city_data();
    double get_max_flow();

public:
    BasicMetricsBuffer();

    void draw() override;
    void handle_input(int ch) override;

    void hide() const override;
    void show() const override;

    ~BasicMetricsBuffer() override;
};



#endif //WATER_MANAGEMENT_BASICMETRICSBUFFER_H
