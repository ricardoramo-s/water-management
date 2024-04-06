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

    PANEL *panel_;

    short color_id_ = 0;
    short box_color_id = 0;

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

    Component(int y, int x);

    /** @brief Default constructor. */
    Component();

    /**
     * @brief Gets the component's ncurses window.
     * @return Pointer to the underlying WINDOW object.
     */
    WINDOW* get_win() const;

    PANEL* get_panel() const;

    std::function<void()> on_select_ = []() -> void {};
    std::function<void()> on_cancel_ = []() -> void {};
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

    void set_color(short id);
    short get_color() const;

    void set_box_color(short id);
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

    virtual void hide() const;
    virtual void show() const;
    virtual void highlight() const;

    virtual void to_front() const;
    virtual void to_back() const;

    const void* get_userptr() const;
    void set_userptr(const void* ptr) const;

    Component* get_next_component() const;
    void set_next_component(Component* component);

    void on_cancel(std::function<void()> callback_function);
    void on_select(std::function<void()> callback_function);
    void on_highlight(std::function<void()> callback_function);

    void on_select() const;
    void on_highlight() const;

    /** @brief Virtual destructor (ensures cleanup when using inheritance). */
    virtual ~Component();
};


#endif //COMPONENT_H
