#ifndef WATER_MANAGEMENT_BUFFER_H
#define WATER_MANAGEMENT_BUFFER_H

#include "vector"
#include "unordered_map"
#include "string"
#include "components/Component.h"

/**
 * @class Buffer
 * @brief Class representing a Buffer.
 *
 * This class is used to manage a buffer in the application. It provides methods to select components, swap selected components, select previous components, quit, check if to quit, get the next buffer, and set the previous buffer.
 */
class Buffer : public Component
{
private:
    bool quit_; ///< Flag to indicate if the buffer should quit
protected:
    Component *currently_selected_component_;  ///< Pointer to the currently selected component
    Component *previously_selected_component_; ///< Pointer to the previously selected component
    Buffer *next_buffer_ = nullptr;            ///< Pointer to the next buffer
    Buffer *previous_buffer_ = nullptr;        ///< Pointer to the previous buffer

public:
    /**
     * @brief Default constructor for the Buffer class.
     */
    Buffer();

    /**
     * @brief Parameterized constructor for the Buffer class.
     *
     * @param height The height of the buffer
     * @param width The width of the buffer
     * @param y The y-coordinate of the buffer
     * @param x The x-coordinate of the buffer
     */
    Buffer(int height, int width, int y, int x);

    /**
     * @brief Selects a component in the buffer.
     *
     * @param component Pointer to the component to select
     */
    void select_component(Component *component);

    /**
     * @brief Swaps the currently selected component with the previously selected component.
     */
    void swap_selected_component();

    /**
     * @brief Selects the previously selected component.
     */
    void select_previous_component();

    /**
     * @brief Quits the buffer.
     */
    void quit();

    /**
     * @brief Checks if the buffer is to quit.
     *
     * @return True if the buffer is to quit, false otherwise
     */
    bool to_quit() const;

    /**
     * @brief Gets the next buffer.
     *
     * @return Pointer to the next buffer
     */
    Buffer *get_next_buffer();

    /**
     * @brief Sets the previous buffer.
     *
     * @param buffer Pointer to the buffer to set as the previous buffer
     */
    void previous_buffer(Buffer *buffer);
};

#endif // WATER_MANAGEMENT_BUFFER_H
