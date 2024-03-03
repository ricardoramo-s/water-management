#ifndef WATER_MANAGEMENT_COLOR_H
#define WATER_MANAGEMENT_COLOR_H

#include "vector"
#include "ColorPair.h"
#include "ncurses.h"


class Color {
private:
    short _r, _g, _b, _id;
    static short _last_color;
    static std::vector<Color*> _colors;

    Color(short r, short g, short b);
public:
    friend class ColorPair;

    static Color* get(short red, short green, short blue);
};


#endif //WATER_MANAGEMENT_COLOR_H
