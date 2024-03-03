#ifndef COMPONENT_H
#define COMPONENT_H
#include "ncurses.h"
#include "panel.h"



class Component {
private:
    int x_, y_, width_, height_;
    WINDOW *win_;

protected:
    Component(int height, int width, int y, int x);
    Component();
    WINDOW* get_win() const;

public:
    virtual void draw() = 0;
    virtual void handle_input() = 0;

    int get_height() const;
    int get_width() const;
    int get_x() const;
    int get_y() const;

    virtual void movewin(int y, int x);
    void refreshwin() const;
    virtual void resizewin(int height, int width);

    virtual ~Component();
};



#endif //COMPONENT_H
