#ifndef WATER_MANAGEMENT_MULTICOMPONENT_H
#define WATER_MANAGEMENT_MULTICOMPONENT_H

#include "ui/components/TextBox.h"

/**
 * @class MultiComponent
 * @brief A Component subclass that manages multiple components of a specific type.
 *
 * The MultiComponent class is a user interface element that allows the management of multiple components of a specific type.
 * It is a subclass of the Component class. The type of components it manages is defined by the template parameter T, which must be a subclass of Component.
 *
 * @tparam T The type of the components managed by this MultiComponent. T must inherit from Component.
 */
template<typename T>
class MultiComponent : public Component {
    static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");

private:
    /** @brief A vector of pointers to the components managed by this MultiComponent. */
    std::vector<T*> components_;

    /** @brief The index of the currently selected component in the components_ vector. */
    int selected_;

    /**
     * @brief Selects the next component in the components_ vector.
     */
    void next_component();

    /**
     * @brief Selects the previous component in the components_ vector.
     */
    void previous_component();

public:
    /**
     * @brief Constructs a MultiComponent.
     */
    MultiComponent();

    /**
     * @brief Adds a component to the components_ vector.
     * @param component Pointer to the component to be added.
     */
    void add_component(T* component);

    /**
     * @brief Gets the index of the currently selected component.
     * @return The index of the currently selected component.
     */
    int get_selected() const;

    /**
     * @brief Gets the currently selected component.
     * @return Pointer to the currently selected component.
     */
    T* get_selected_component() const;

    /**
     * @brief Gets a specific component.
     * @param i The index of the component to get.
     * @return Pointer to the component at index i.
     */
    T* get_component(int i) const;

    /**
     * @brief Draws the MultiComponent and its components.
     *
     * This function is responsible for drawing the MultiComponent and its components on the screen.
     */
    void draw() override;

    /**
     * @brief Handles keyboard input - processes a single key press.
     * @param ch The code of the pressed key.
     *
     * This function is responsible for handling user input and updating the MultiComponent and its components accordingly.
     */
    void handle_input(int ch) override;

    /**
     * @brief Hides the MultiComponent and its components.
     */
    void hide() const override;

    /**
     * @brief Shows the MultiComponent and its components.
     */
    void show() const override;

    /**
     * @brief Destructor for the MultiComponent.
     *
     * This function is responsible for cleaning up when the MultiComponent is no longer needed.
     */
    ~MultiComponent() override;
};


#endif //WATER_MANAGEMENT_MULTICOMPONENT_H
