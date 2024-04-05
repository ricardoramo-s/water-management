#ifndef WATER_MANAGEMENT_BASICMETRICSBUFFER_H
#define WATER_MANAGEMENT_BASICMETRICSBUFFER_H

#include "Buffer.h"
#include "ui/components/SearchBox.h"
#include "components/TextLabel.h"
#include "BalanceBuffer.h"


class BasicMetricsBuffer : public Buffer {
private:
    SearchBox *search_box_;
    TextLabel *id_, *code_, *demand_, *population_;
    TextLabel *balance_;

    BalanceBuffer *balance_buffer_;

public:
    BasicMetricsBuffer();

    void draw() override;
    void handle_input(int ch) override;

    void hide() const override;
    void show() const override;

    ~BasicMetricsBuffer() override;
};



#endif //WATER_MANAGEMENT_BASICMETRICSBUFFER_H
