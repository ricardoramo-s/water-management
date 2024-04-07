#ifndef WATER_MANAGEMENT_MAINBUFFER_H
#define WATER_MANAGEMENT_MAINBUFFER_H

#include "components/TextLabel.h"
#include "BasicMetricsBuffer.h"
#include "Buffer.h"
#include "FailureBuffer.h"

/**
 * @class MainBuffer
 * @brief A class that represents the main buffer in the water management system.
 *
 * The MainBuffer class is responsible for managing the main buffer of the water management system. It inherits from the Buffer class and contains references to the basic metrics and failure buffers.
 */
class MainBuffer : public Buffer {
private:
    /**
     * @brief A pointer to the TextLabel representing the basic metrics.
     */
    TextLabel *basic_metrics_;

    /**
     * @brief A pointer to the TextLabel representing the failure.
     */
    TextLabel *failure_;

    /**
     * @brief A pointer to the BasicMetricsBuffer.
     */
    BasicMetricsBuffer *metrics_buffer_;

    /**
     * @brief A pointer to the FailureBuffer.
     */
    FailureBuffer *failure_buffer_;

public:
    /**
     * @brief Constructs a new MainBuffer object.
     */
    MainBuffer();

    /**
     * @brief Draws the MainBuffer.
     *
     * This function is responsible for drawing the MainBuffer on the screen.
     */
    void draw() override;

    /**
     * @brief Handles input events for the MainBuffer.
     *
     * @param ch The character representing the input event.
     */
    void handle_input(int ch) override;

    /**
     * @brief Hides the MainBuffer.
     *
     * This function is responsible for hiding the MainBuffer from the screen.
     */
    void hide() const override;

    /**
     * @brief Shows the MainBuffer.
     *
     * This function is responsible for showing the MainBuffer on the screen.
     */
    void show() const override;

    /**
     * @brief Destroys the MainBuffer object.
     *
     * This function is responsible for cleaning up any resources used by the MainBuffer object when it is no longer needed.
     */
    ~MainBuffer();
};


#endif //WATER_MANAGEMENT_MAINBUFFER_H
