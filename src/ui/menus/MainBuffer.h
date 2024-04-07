#ifndef WATER_MANAGEMENT_MAINBUFFER_H
#define WATER_MANAGEMENT_MAINBUFFER_H

#include "components/TextLabel.h"
#include "BasicMetricsBuffer.h"
#include "Buffer.h"
#include "FailureBuffer.h"

class MainBuffer : public Buffer {
private:
    TextLabel *basic_metrics_, *failure_;

    BasicMetricsBuffer *metrics_buffer_ = nullptr;
    FailureBuffer *failure_buffer_ = nullptr;

public:
    MainBuffer();

    void draw() override;
    void handle_input(int ch) override;

    void hide() const override;
    void show() const override;

    ~MainBuffer();
};


#endif //WATER_MANAGEMENT_MAINBUFFER_H
