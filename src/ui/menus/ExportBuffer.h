#ifndef WATER_MANAGEMENT_EXPORTBUFFER_H
#define WATER_MANAGEMENT_EXPORTBUFFER_H

#include "Buffer.h"
#include "components/InputBox.h"
#include "components/TextLabel.h"

class ExportBuffer : public Buffer {
private:
    InputBox *input_box_;
    TextLabel *export_output_;

    std::string export_data();
    void create_output(std::string string);
public:
    ExportBuffer();

    void draw() override;
    void handle_input(int ch) override;

    void hide() const override;
    void show() const override;

    ~ExportBuffer() override;
};


#endif //WATER_MANAGEMENT_EXPORTBUFFER_H
