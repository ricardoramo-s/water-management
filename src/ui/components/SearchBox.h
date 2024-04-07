#ifndef WATER_MANAGEMENT_SEARCHBOX_H
#define WATER_MANAGEMENT_SEARCHBOX_H

#include "ui/components/TextBox.h"
#include "ui/components/InputBox.h"
#include "vector"
#include "components/MultiComponent.h"
#include "functional"
#include "unordered_set"

/**
 * @class SearchBox
 * @brief A Component subclass that manages a search box.
 *
 * The SearchBox class is a user interface element that allows the management of a search box.
 * It is a subclass of the Component class. The search box is composed of a MultiComponent of TextBoxes and an InputBox.
 */
class SearchBox : public Component {
    /** @brief A MultiComponent of TextBoxes that displays the search results. */
    MultiComponent<TextBox>* multi_text_box_;

    /** @brief An InputBox that captures the user's input. */
    InputBox* input_box_;

    /** @brief A vector of unordered sets of strings that represent the search options. */
    std::vector<std::unordered_set<std::string>> options_;

    /** @brief The color id of the highlighted option. */
    short highlighted_color_id_ = 0;

    /** @brief A flag that indicates whether an update is requested. */
    bool request_update_ = false;

public:
    /**
     * @brief Constructs a SearchBox with a given size and position.
     * @param height The height of the SearchBox.
     * @param width The width of the SearchBox.
     * @param y The y-coordinate of the SearchBox.
     * @param x The x-coordinate of the SearchBox.
     */
    SearchBox(int height, int width, int y, int x);

    /**
     * @brief Adds a set of options to the SearchBox.
     * @param options A vector of strings that represent the options.
     * @param header A string that represents the header of the options.
     */
    void add_options(std::vector<std::string>& options, std::string header);

    /**
     * @brief Sets the color id of the highlighted option.
     * @param id The color id to set.
     */
    void set_highlighted_color(short id);

    /**
     * @brief Returns the selected string.
     * @return The selected string.
     */
    std::string get_selected_string() const;

    /**
     * @brief Returns the index of the selected option.
     * @return The index of the selected option.
     */
    int get_selected() const;

    /**
     * @brief Draws the SearchBox and its components.
     */
    void draw() override;

    /**
     * @brief Handles keyboard input - processes a single key press.
     * @param ch The code of the pressed key.
     */
    void handle_input(int ch) override;

    /**
     * @brief Removes the selected option.
     */
    void remove();

    /**
     * @brief Adds a string to the options.
     * @param string The string to add.
     */
    void add(std::string string);

    /**
     * @brief Adds a string to the options at a given index.
     * @param i The index at which to add the string.
     * @param string The string to add.
     */
    void add(int i, std::string string);

    /**
     * @brief Clears the options.
     */
    void clear();

    /**
     * @brief Hides the SearchBox and its components.
     */
    void hide() const override;

    /**
     * @brief Shows the SearchBox and its components.
     */
    void show() const override;

    /**
     * @brief Destructor for the SearchBox.
     *
     * This function is responsible for cleaning up when the SearchBox is no longer needed.
     */
    ~SearchBox() override;
};

#endif //WATER_MANAGEMENT_SEARCHBOX_H
