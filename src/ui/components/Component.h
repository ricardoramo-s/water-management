#ifndef COMPONENT_H
#define COMPONENT_H
#include "ncurses.h"
#include "panel.h"

/**
 * @class Component
 * @brief Base class for reusable user interface components within an ncurses application.
 */
class Component {
private:
    /** @brief Horizontal position (in characters). */
    int x_;

    /** @brief Vertical position (in characters). */
    int y_;

    /** @brief Width of the component (in characters). */
    int width_;

    /** @brief Height of the component (in characters). */
    int height_;

    /** @brief The underlying ncurses window object. */
    WINDOW *win_;

protected:
    /**
     * @brief Constructor for component initialization.
     * @param height Height of the component (in characters).
     * @param width Width of the component (in characters).
     * @param y Vertical position (in characters).
     * @param x Horizontal position (in characters).
     */
    Component(int height, int width, int y, int x);

    Component(int y, int x);

    /** @brief Default constructor. */
    Component();

    /**
     * @brief Gets the component's ncurses window.
     * @return Pointer to the underlying WINDOW object.
     */
    WINDOW* get_win() const;

    void set_win(WINDOW* win);

public:
    /**
     * @brief Renders the component (must be implemented by derived classes).
     */
    virtual void draw() = 0;

    /**
     * @brief Handles input events (must be implemented by derived classes).
     */
    virtual void handle_input(int ch) = 0;

    /** @brief Gets the height of the component's window (in characters). */
    int get_height() const;

    /** @brief Gets the width of the component's window (in characters). */
    int get_width() const;

    /** @brief Gets the horizontal position of the component (in characters). */
    int get_x() const;

    /** @brief Gets the vertical position of the component (in characters). */
    int get_y() const;

    /**
     * @brief Moves the component's window.
     * @param y New vertical position (in characters).
     * @param x New horizontal position (in characters).
     */
    virtual void movewin(int y, int x);

    /** @brief Refreshes the component's window display. */
    void refreshwin() const;

    /**
     * @brief Resizes the component's window.
     * @param height New window height (in characters).
     * @param width New window width (in characters).
     */
    virtual void resizewin(int height, int width);

    /** @brief Virtual destructor (ensures cleanup when using inheritance). */
    virtual ~Component();
};


#endif //COMPONENT_H
