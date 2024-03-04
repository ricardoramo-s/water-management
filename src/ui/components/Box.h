#ifndef WATER_MANAGEMENT_BOX_H
#define WATER_MANAGEMENT_BOX_H


#include <type_traits>
#include "Component.h"
#include "TextBox.h"

/**
 * @class Box
 * @brief A templated container class to add framing and headers to Component-derived objects.
 * @tparam T The type of Component subclass being contained by the Box.
 */
template <typename T>
class Box : public Component {
    static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");

private:
    /** @brief Pointer to the contained Component-derived object. */
    T* component_;

    /** @brief Header text to display above the contained component. */
    std::string header_;

public:
    /**
     * @brief Constructs a Box with a contained component.
     * @param component Pointer to the Component-derived object to be contained.
     */
    explicit Box(T* component);

    /**
     * @brief Constructs a Box with a contained component and a header.
     * @param component Pointer to the Component-derived object to be contained.
     * @param header The header text to be displayed.
     */
    Box(T* component, std::string header);

    /**
     * @brief Gets the contained component.
     * @return Pointer to the contained Component object.
     */
    T* get_component();

    /**
     * @brief Sets the header text for the Box.
     * @param header The new header text.
     */
    void set_header(std::string header);

    /**
     * @brief Overrides the Component::draw() function to render the box and contained component.
     */
    void draw() override;

    /**
     * @brief Overrides the Component::handle_input() function (implementation dependent on contained component).
     */
    void handle_input() override;

    /**
     * @brief Adjusts the box and the contained component position.
     * @param y Vertical offset for the contained component (and thereby the box).
     * @param x Horizontal offset for the contained component (and thereby the box).
     */
    void move_with_component(int y, int x);

    /**
     * @brief Adjusts the box and the contained component size.
     * @param height New height for the contained component (and thereby the box).
     * @param width New width for the contained component (and thereby the box).
     */
    void resize_with_component(int height, int width);

    /** @brief Destructor for the Box. */
    ~Box();
};


#endif //WATER_MANAGEMENT_BOX_H
