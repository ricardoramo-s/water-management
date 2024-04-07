#ifndef WATER_MANAGEMENT_INPUTBOX_H
#define WATER_MANAGEMENT_INPUTBOX_H

#include "Component.h"
#include "functional"
#include "string"

/**
 * @class InputBox
 * @brief A Component subclass providing a labeled field for user text input.
 *
 * The InputBox class is a user interface element that allows the user to enter text.
 * It is a subclass of the Component class.
 */
class InputBox : public Component {
protected:
    /** @brief The currently entered input text. */
    std::string input_text_;

    /** @brief Default text displayed when input is empty. */
    std::string default_text_;

    /** @brief Tracks if the user inputted text. */
    bool input_flag_ = true;

    /** @brief The header text of the InputBox. */
    std::string header_;

public:
    /**
     * @brief Constructs an InputBox with specified dimensions, position, and default text.
     * @param width Width of the input field (in characters).
     * @param y Vertical position (in characters).
     * @param x Horizontal position (in characters).
     * @param default_text Text displayed when the input field is empty.
     */
    InputBox(int width, int y, int x, std::string default_text);

    /**
     * @brief Renders the InputBox with label and current input.
     *
     * This function is responsible for drawing the InputBox on the screen.
     */
    void draw() override;

    /**
     * @brief Handles keyboard input - processes a single key press.
     * @param ch The code of the pressed key.
     *
     * This function is responsible for handling user input and updating the InputBox accordingly.
     */
    void handle_input(int ch) override;

    /**
     * @brief Gets the input flag.
     * @return The current state of the input flag.
     */
    bool get_input_flag() const;

    /**
     * @brief Gets the currently entered input text.
     * @return The input text string.
     */
    std::string get_input_text() const;

    /**
     * @brief Sets the header text of the InputBox.
     * @param header The new header text.
     */
    void set_header_(std::string header);

    /**
     * @brief Clears the input text.
     *
     * This function is responsible for clearing the input text of the InputBox.
     */
    void clear();

    /**
     * @brief Destructor for the InputBox.
     *
     * This function is responsible for cleaning up when the InputBox is no longer needed.
     */
    ~InputBox() override = default;
};

#endif //WATER_MANAGEMENT_INPUTBOX_H
