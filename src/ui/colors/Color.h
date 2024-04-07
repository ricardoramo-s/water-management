#ifndef WATER_MANAGEMENT_COLOR_H
#define WATER_MANAGEMENT_COLOR_H

#include "vector"
#include "ColorPair.h"
#include "ncurses.h"


class Color {
private:
    short _r, g_, b_, id_;
    static short last_color_;
    static std::vector<Color*> colors_;

    Color(short r, short g, short b);
public:
    friend class ColorPair;

    static Color* get(short red, short green, short blue);
};


#endif //WATER_MANAGEMENT_COLOR_H
