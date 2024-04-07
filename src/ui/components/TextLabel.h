#ifndef WATER_MANAGEMENT_TEXTLABEL_H
#define WATER_MANAGEMENT_TEXTLABEL_H


#include "Component.h"
#include "colors/ColorPair.h"
#include "string"

/**
 * @class TextLabel
 * @brief A Component subclass that displays a single line of non-editable text.
*/
class TextLabel : public Component {
private:
    /** @brief The text content of the label. */
    std::string text_;

public:

    /**
     * @brief Constructs a TextLabel with specified position and text content.
     * @param y Vertical position (in characters).
     * @param x Horizontal position (in characters).
     * @param text The text to be displayed by the label.
     */
    TextLabel(int y, int x, std::string text);
    TextLabel(int width, int y, int x);

    /**
     * @brief Renders the TextLabel's content to the screen.
     */
    void draw() override;

    void set_text(std::string text);

    void handle_input(int ch) override;

    /** @brief Destructor for the TextLabel class */
    ~TextLabel() override = default;
};


#endif //WATER_MANAGEMENT_TEXTLABEL_H
