//
// Created by Ricardo Ramos on 05/03/2024.
//

#ifndef WATER_MANAGEMENT_OPTIONMENU_H
#define WATER_MANAGEMENT_OPTIONMENU_H


#include "Component.h"
#include "TextLabel.h"
#include "vector"

/**
 * @class OptionMenu
 * @brief A Component subclass that manages a menu of options.
 *
 * The OptionMenu class is a user interface element that allows the management of a menu of options.
 * It is a subclass of the Component class. Each option is represented by a TextLabel.
 */
class OptionMenu : public Component {
private:
    /** @brief A vector of pointers to the TextLabel options. */
    std::vector<TextLabel*> options_;

    /** @brief The index of the currently selected option in the options_ vector. */
    int selected_ = -1;

    /**
     * @brief Shifts the selected option up in the options_ vector.
     */
    void shift_selected_up();

    /**
     * @brief Shifts the selected option down in the options_ vector.
     */
    void shift_selected_down();

public:
    /**
     * @brief Constructs an OptionMenu with a given position and options.
     * @param y The y-coordinate of the OptionMenu.
     * @param x The x-coordinate of the OptionMenu.
     * @param options A vector of pointers to the TextLabel options.
     */
    OptionMenu(int y, int x, std::vector<TextLabel*>& options);

    /**
     * @brief Constructs an OptionMenu with a given position.
     * @param y The y-coordinate of the OptionMenu.
     * @param x The x-coordinate of the OptionMenu.
     */
    OptionMenu(int y, int x);

    /**
     * @brief Default constructor for the OptionMenu.
     */
    OptionMenu();

    /**
     * @brief Adds an option to the options_ vector.
     * @param option Pointer to the TextLabel option to be added.
     */
    void add_option(TextLabel* option);

    /**
     * @brief Adds an option with a given position and text to the options_ vector.
     * @param y The y-coordinate of the option.
     * @param text The text of the option.
     */
    void add_option(int y, std::string text);

    /**
     * @brief Selects an option in the options_ vector.
     * @param i The index of the option to select.
     */
    void select(int i);

    /**
     * @brief Draws the OptionMenu and its options.
     *
     * This function is responsible for drawing the OptionMenu and its options on the screen.
     */
    void draw() override;

    /**
     * @brief Handles keyboard input - processes a single key press.
     * @param ch The code of the pressed key.
     *
     * This function is responsible for handling user input and updating the OptionMenu and its options accordingly.
     */
    void handle_input(int ch) override;

    /**
     * @brief Shows the OptionMenu and its options.
     */
    void show() const override;

    /**
     * @brief Hides the OptionMenu and its options.
     */
    void hide() const override;

    /**
     * @brief Destructor for the OptionMenu.
     *
     * This function is responsible for cleaning up when the OptionMenu is no longer needed.
     */
    ~OptionMenu() override;
};

#endif //WATER_MANAGEMENT_OPTIONMENU_H
