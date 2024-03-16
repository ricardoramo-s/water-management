#ifndef WATER_MANAGEMENT_INPUTBOX_H
#define WATER_MANAGEMENT_INPUTBOX_H


#include "Component.h"
#include "string"

/**
 * @class InputBox
 * @brief A Component subclass providing a labeled field for user text input.
 */
class InputBox : public Component {
protected:
    /** @brief The currently entered input text. */
    std::string input_text_;

    /** @brief Default text displayed when input is empty. */
    std::string default_text_;

    /** @brief Tracks if the user inputted text. */
    bool input_flag_ = true;

    std::string header_;

    std::function<void()> on_cancel_ = []() -> void {};
    std::function<void()> on_select_ = []() -> void {};

public:
    /**
     * @brief Constructs an InputBox with specified dimensions, position, and default text.
     * @param width Width of the input field (in characters).
     * @param y Vertical position (in characters).
     * @param x Horizontal position (in characters).
     * @param default_text Text displayed when the input field is empty.
     */
    InputBox(int width, int y, int x, std::string default_text);

    InputBox(int width, int y, int x, std::string default_text, std::string header, short text_color_id, short box_color_id, std::function<void()> on_select, std::function<void()> on_cancel);

    /**
     * @brief Renders the InputBox with label and current input.
     */
    void draw() override;

    /**
     * @brief Handles keyboard input - processes a single key press.
     * @param ch The code of the pressed key.
     */
    void handle_input(int ch) override;

    bool get_input_flag() const;

    /**
     * @brief Gets the currently entered input text.
     * @return The input text string.
     */
    std::string get_input_text() const;

    void set_header_(std::string header);

    void clear();

    void on_select(std::function<void()> callback_function);
    void on_cancel(std::function<void()> callback_function);
};


#endif //WATER_MANAGEMENT_INPUTBOX_H
