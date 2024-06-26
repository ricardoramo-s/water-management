#ifndef WATER_MANAGEMENT_TEXTBOX_H
#define WATER_MANAGEMENT_TEXTBOX_H

#include "Component.h"
#include "functional"
#include "vector"
#include "string"

/**
 * @class TextBox
 * @brief A Component subclass that displays multiple lines of text, with scrolling and selection capabilities.
 *
 * The TextBox class is a user interface element that allows the management of a text box.
 * It is a subclass of the Component class. The text box is composed of multiple lines of text,
 * with scrolling and selection capabilities.
 */
class TextBox : public Component {
private:
    /** @brief Vector of text lines displayed by the TextBox */
    std::vector<std::string> lines_;

    /** @brief Header of the TextBox */
    std::string header_{};

    /** @brief Index of the currently selected line (-1 indicates no selection) */
    int selected_ = -1;

    /** @brief Current minimum line index displayed in the TextBox's window */
    int min_ = 0;

    /** @brief Current maximum line index displayed in the TextBox's window */
    int max_ = 0;

    /** @brief Controls whether lines are displayed in standard or reversed order */
    bool reversed_ = false;

    /** @brief Color id of the highlighted line */
    short highlighted_color_ = 0;

    /** @brief Updates the minimum line index, changing the maximum line index accordingly. */
    void set_min_(int min);

    /** @brief Updates the maximum line index, changing the minimum line index accordingly. */
    void set_max_(int max);

    /** @brief Shifts the TextBox's display window down.*/
    void shift_window_down();

    /** @brief Shifts the TextBox's display window up.*/
    void shift_window_up();

    /** @brief Shifts the selected line up, updating the display window accordingly.*/
    void shift_selected_up();

    /** @brief Shifts the selected line down, updating the display window accordingly.*/
    void shift_selected_down();

public:
    /**
     * @brief Constructs a TextBox with specified dimensions and display ordering.
     * @param height Height of the TextBox (in characters).
     * @param width Width of the TextBox (in characters).
     * @param y Vertical position (in characters).
     * @param x Horizontal position (in characters).
     * @param reversed If true, lines are displayed in bottom-to-top order.
     */
    TextBox(int height, int width, int y, int x, bool reversed);

    /**
     * @brief Gets all the lines currently displayed in the TextBox.
     * @return A copy of the vector containing the displayed lines.
     */
    std::vector<std::string> get_lines_();

    /**
     * @brief Updates the TextBox with a new set of lines.
     * @param lines A vector of strings to be displayed.
     */
    void set_lines_(std::vector<std::string>& lines);

    /**
     * @brief Sets the header of the TextBox.
     * @param header The header to be set.
     */
    void set_header_(std::string header);

    /**
     * @brief Gets the text content of the currently selected line.
     * @return  The selected line's content, or an empty string if no selection is made.
     */
    std::string get_selected_string() const;

    /**
     * @brief Gets the index of the currently selected line.
     * @return The index of the selected line, or -1 if no line is selected.
     */
    int get_selected() const;

    /**
     * @brief Selects a line by its index.
     * @param i Zero-based index of the line to select.
     */
    void select(int i);

    /**
     * @brief Selects a line by matching its textual content.
     * @param text Text of the line to be selected.
     */
    void select(std::string& text);

    /**
     * @brief Sets the color id of the highlighted line.
     * @param id The color id to set.
     */
    void set_highlighted_color(short id);

    /**
     * @brief Overrides Component::draw() to render the TextBox content.
     */
    void draw() override;

    /**
     * @brief Handles keyboard input - processes a single key press.
     * @param ch The code of the pressed key.
     */
    void handle_input(int ch) override;

    /**
     * @brief Removes the selected line from the TextBox.
     */
    void remove();

    /**
     * @brief Adds a string to the TextBox.
     * @param string The string to add.
     */
    void add(std::string string);

    /**
     * @brief Destructor for the TextBox.
     */
    ~TextBox() override = default;
};

#endif //WATER_MANAGEMENT_TEXTBOX_H
