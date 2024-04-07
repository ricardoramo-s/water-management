#include "Color.h"

short Color::last_color_ = 255;
std::vector<Color*> Color::colors_ = std::vector<Color*>();

Color::Color(short r, short g, short b) : _r(r), g_(g), b_(b), id_(last_color_--) {
    init_color(id_, r, g, b);
    colors_.push_back(this);
}

Color* Color::get(short red, short green, short blue) {
    for (auto& color : colors_) {
        if (color->_r == red && color->g_ == green && color->b_ == blue) {
            return color;
        }
    }

    return new Color(red, green, blue);
}
