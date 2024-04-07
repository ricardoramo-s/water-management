#ifndef WATER_MANAGEMENT_EXPORTBUFFER_H
#define WATER_MANAGEMENT_EXPORTBUFFER_H

#include "Buffer.h"
#include "components/InputBox.h"
#include "components/TextLabel.h"

/**
 * @class ExportBuffer
 * @brief A class that represents an export buffer.
 *
 * This class is derived from the Buffer class and it is used to manage the export buffer.
 */
class ExportBuffer : public Buffer {
private:
    /**
     * @brief A pointer to an InputBox object.
     */
    InputBox *input_box_;

    /**
     * @brief A pointer to a TextLabel object.
     */
    TextLabel *export_output_;

    /**
     * @brief Exports data.
     * @return A string representing the exported data.
     */
    std::string export_data();

    /**
     * @brief Creates output.
     * @param string The string to be outputted.
     */
    void create_output(std::string string);
public:
    /**
     * @brief Default constructor.
     */
    ExportBuffer();

    /**
     * @brief Draws the export buffer.
     */
    void draw() override;

    /**
     * @brief Handles input events.
     * @param ch The character representing the input event.
     */
    void handle_input(int ch) override;

    /**
     * @brief Hides the export buffer.
     */
    void hide() const override;

    /**
     * @brief Shows the export buffer.
     */
    void show() const override;

    /**
     * @brief Default destructor.
     */
    ~ExportBuffer() override;
};


#endif //WATER_MANAGEMENT_EXPORTBUFFER_H
