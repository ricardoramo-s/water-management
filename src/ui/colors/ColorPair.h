#ifndef WATER_MANAGEMENT_COLORPAIR_H
#define WATER_MANAGEMENT_COLORPAIR_H

#include "unordered_set"
#include "Color.h"
#include <ncurses.h>
#include <functional>

// Forward declare the Color class
class Color;

class ColorPair {
private:
    short _id;
    Color* _foreground, *_background;

    static short _last_pair;
    static std::vector<ColorPair*> _pairs;

    ColorPair(Color* foreground, Color* background);
public:
    static void activate(WINDOW* win, short fr, short fg, short fb, short br, short bg, short bb);
};

#endif //WATER_MANAGEMENT_COLORPAIR_H
