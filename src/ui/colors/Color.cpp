#include "Color.h"

short Color::_last_color = 1;
auto Color::_colors = std::vector<Color*>();

Color::Color(short r, short g, short b) : _r(r), _g(g), _b(b), _id(_last_color++) {
    init_color(_id, r, g, b);
    _colors.push_back(this);
}

Color* Color::get(short red, short green, short blue) {
    for (auto& color : _colors) {
        if (color->_r == red && color->_g == green && color->_b == blue) {
            return color;
        }
    }

    return new Color(red, green, blue);
}
