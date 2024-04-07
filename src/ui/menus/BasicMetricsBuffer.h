#ifndef WATER_MANAGEMENT_BASICMETRICSBUFFER_H
#define WATER_MANAGEMENT_BASICMETRICSBUFFER_H

#include "Buffer.h"
#include "ui/components/SearchBox.h"
#include "components/TextLabel.h"
#include "BalanceBuffer.h"
#include "components/OptionMenu.h"
#include "ExportBuffer.h"
#include "BaseClasses/City.h"


/**
 * @class BasicMetricsBuffer
 * @brief A Buffer subclass that manages the basic metrics buffer.
 *
 * The BasicMetricsBuffer class is a user interface element that allows the management of basic metrics buffer.
 * It is a subclass of the Buffer class.
 */
class BasicMetricsBuffer : public Buffer {
private:
    SearchBox *search_box_; ///< Search box for user input
    TextLabel *max_flow_; ///< Text label for maximum flow
    TextLabel *id_, *code_, *demand_, *flow_, *deficit_, *population_; ///< Text labels for various city metrics
    TextLabel *balance_, *export_; ///< Text labels for balance and export

    BalanceBuffer *balance_buffer_; ///< Balance buffer
    ExportBuffer *export_buffer_; ///< Export buffer

    /**
     * @brief Reads city data.
     */
    void read_city_data();

    /**
     * @brief Gets the maximum flow.
     * @return The maximum flow.
     */
    double get_max_flow();

public:
    /**
     * @brief Constructs a BasicMetricsBuffer.
     */
    BasicMetricsBuffer();

    /**
     * @brief Renders the BasicMetricsBuffer's content to the screen.
     */
    void draw() override;

    /**
     * @brief Handles keyboard input - processes a single key press.
     * @param ch The code of the pressed key.
     */
    void handle_input(int ch) override;

    /**
     * @brief Hides the BasicMetricsBuffer.
     */
    void hide() const override;

    /**
     * @brief Shows the BasicMetricsBuffer.
     */
    void show() const override;

    /**
     * @brief Destructor for the BasicMetricsBuffer class.
     */
    ~BasicMetricsBuffer() override;
};



#endif //WATER_MANAGEMENT_BASICMETRICSBUFFER_H
