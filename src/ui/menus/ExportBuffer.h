#ifndef WATER_MANAGEMENT_EXPORTBUFFER_H
#define WATER_MANAGEMENT_EXPORTBUFFER_H

#include "Buffer.h"
#include "components/InputBox.h"

class ExportBuffer : public Buffer {
private:
    InputBox *input_box_;

public:
    ExportBuffer();

    void draw() override;
    void handle_input(int ch) override;

    void hide() const override;
    void show() const override;

    ~ExportBuffer() override;
};


#endif //WATER_MANAGEMENT_EXPORTBUFFER_H
