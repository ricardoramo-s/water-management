#ifndef WATER_MANAGEMENT_BALANCEBUFFER_H
#define WATER_MANAGEMENT_BALANCEBUFFER_H

#include "components/TextLabel.h"
#include "menus/Buffer.h"

/**
 * @class BalanceBuffer
 * @brief A Buffer subclass that manages the balance buffer.
 *
 * The BalanceBuffer class is a user interface element that allows the management of balance buffer.
 * It is a subclass of the Buffer class.
 */
class BalanceBuffer : public Buffer {
private:
    /** @brief TextLabel for old average. */
    TextLabel *old_average_;
    /** @brief TextLabel for old variance. */
    TextLabel *old_variance_;
    /** @brief TextLabel for old maximum difference. */
    TextLabel *old_max_diff_;
    /** @brief TextLabel for new average. */
    TextLabel *new_average_;
    /** @brief TextLabel for new variance. */
    TextLabel *new_variance_;
    /** @brief TextLabel for new maximum difference. */
    TextLabel *new_max_diff_;
    /** @brief TextLabel for meeting demands. */
    TextLabel *meets_demands_;

    /**
     * @brief Checks if the demand is met.
     * @return True if the demand is met, false otherwise.
     */
    bool meets_demand();

public:
    /**
     * @brief Constructs a BalanceBuffer.
     */
    BalanceBuffer();

    /**
     * @brief Overrides Buffer::draw() to render the BalanceBuffer content.
     */
    void draw() override;

    /**
     * @brief Handles keyboard input - processes a single key press.
     * @param ch The code of the pressed key.
     */
    void handle_input(int ch) override;

    /**
     * @brief Hides the BalanceBuffer.
     */
    void hide() const override;

    /**
     * @brief Shows the BalanceBuffer.
     */
    void show() const override;

    /**
     * @brief Destructor for the BalanceBuffer.
     */
    ~BalanceBuffer() override;
};

#endif //WATER_MANAGEMENT_BALANCEBUFFER_H
