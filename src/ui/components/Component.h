#ifndef COMPONENT_H
#define COMPONENT_H
#include "ncurses.h"
#include "functional"
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

    /** @brief The underlying ncurses panel object. */
    PANEL *panel_;

    /** @brief The color id of the component. */
    short color_id_ = 0;

    /** @brief The color id of the box. */
    short box_color_id = 0;

    /** @brief Pointer to the next component. */
    Component* next_component_ = nullptr;

protected:
    /**
     * @brief Constructor for component initialization.
     * @param height Height of the component (in characters).
     * @param width Width of the component (in characters).
     * @param y Vertical position (in characters).
     * @param x Horizontal position (in characters).
     */
    Component(int height, int width, int y, int x);

    /**
     * @brief Constructor for component initialization.
     * @param y Vertical position (in characters).
     * @param x Horizontal position (in characters).
     */
    Component(int y, int x);

    /** @brief Default constructor. */
    Component();

    /**
     * @brief Gets the component's ncurses window.
     * @return Pointer to the underlying WINDOW object.
     */
    WINDOW* get_win() const;

    /**
     * @brief Gets the component's ncurses panel.
     * @return Pointer to the underlying PANEL object.
     */
    PANEL* get_panel() const;

    /** @brief Callback function to be called when the component is selected. */
    std::function<void()> on_select_ = []() -> void {};

    /** @brief Callback function to be called when the component is cancelled. */
    std::function<void()> on_cancel_ = []() -> void {};

    /** @brief Callback function to be called when the component is highlighted. */
    std::function<void()> on_highlight_ = []() -> void {};

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
     * @brief Sets the color of the component.
     * @param id The color id.
     */
    void set_color(short id);

    /** @brief Gets the color of the component. */
    short get_color() const;

    /**
     * @brief Sets the color of the box.
     * @param id The color id.
     */
    void set_box_color(short id);

    /** @brief Gets the color of the box. */
    short get_box_color() const;

    /**
     * @brief Moves the component's window.
     * @param y New vertical position (in characters).
     * @param x New horizontal position (in characters).
     */
    virtual void move(int y, int x);

    /** @brief Refreshes the component's window display. */
    void refreshwin() const;

    /**
     * @brief Resizes the component's window.
     * @param height New window height (in characters).
     * @param width New window width (in characters).
     */
    virtual void resize(int height, int width);

    /** @brief Hides the component. */
    virtual void hide() const;

    /** @brief Shows the component. */
    virtual void show() const;

    /** @brief Highlights the component. */
    virtual void highlight() const;

    /** @brief Brings the component to the front. */
    virtual void to_front() const;

    /** @brief Sends the component to the back. */
    virtual void to_back() const;

    /** @brief Gets the next component. */
    Component* get_next_component() const;

    /**
     * @brief Sets the next component.
     * @param component Pointer to the next component.
     */
    void set_next_component(Component* component);

    /**
     * @brief Sets the callback function to be called when the component is cancelled.
     * @param callback_function The callback function.
     */
    void on_cancel(std::function<void()> callback_function);

    /**
     * @brief Sets the callback function to be called when the component is selected.
     * @param callback_function The callback function.
     */
    void on_select(std::function<void()> callback_function);

    /**
     * @brief Sets the callback function to be called when the component is highlighted.
     * @param callback_function The callback function.
     */
    void on_highlight(std::function<void()> callback_function);

    /** @brief Calls the on_select callback function. */
    void on_select() const;

    /** @brief Calls the on_highlight callback function. */
    void on_highlight() const;

    /** @brief Virtual destructor (ensures cleanup when using inheritance). */
    virtual ~Component();
};

#endif //COMPONENT_H
