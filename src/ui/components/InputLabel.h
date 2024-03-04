#ifndef WATER_MANAGEMENT_INPUTLABEL_H
#define WATER_MANAGEMENT_INPUTLABEL_H


#include "Component.h"
#include "string"

/**
 * @class InputLabel
 * @brief A Component subclass providing a labeled field for user text input.
 */
class InputLabel : public Component {
private:
    /** @brief The currently entered input text. */
    std::string input_text_;

    /** @brief Default text displayed when input is empty. */
    std::string default_text_;

    /** @brief Tracks if active user input is allowed. */
    bool input_flag_ = true;

public:
    /**
     * @brief Constructs an InputLabel with specified width and position.
     * @param width Width of the input field (in characters).
     * @param y Vertical position (in characters).
     * @param x Horizontal position (in characters).
     */
    InputLabel(int width, int y, int x);

    /**
     * @brief Constructs an InputLabel with specified dimensions, position, and default text.
     * @param width Width of the input field (in characters).
     * @param y Vertical position (in characters).
     * @param x Horizontal position (in characters).
     * @param default_text Text displayed when the input field is empty.
     */
    InputLabel(int width, int y, int x, std::string default_text);

    /**
     * @brief Renders the InputLabel with label and current input.
     */
    void draw() override;

    /**
     * @brief Handles keyboard input - awaits a single character press.
     */
    void handle_input() override;

    /**
     * @brief Handles keyboard input - processes a single key press.
     * @param ch The code of the pressed key.
     */
    void handle_input(int ch);

    /**
     * @brief Gets the input flag status (for input control).
     * @return true if the component is accepting input, false otherwise.
     */
    bool get_input_flag() const;

    /**
     * @brief Gets the currently entered input text.
     * @return The input text string.
     */
    std::string get_input_text() const;
};


#endif //WATER_MANAGEMENT_INPUTLABEL_H
