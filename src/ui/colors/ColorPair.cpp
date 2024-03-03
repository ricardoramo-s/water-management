#include "ColorPair.h"

short ColorPair::_last_pair = 1;

std::vector<ColorPair*> ColorPair::_pairs = std::vector<ColorPair*>();

ColorPair::ColorPair(Color* foreground, Color* background) : _id(_last_pair++), _foreground(foreground), _background(background) {
    init_pair(_id, _foreground->_id, _background->_id);
    _pairs.push_back(this);
}

void ColorPair::activate(WINDOW* win, short fr, short fg, short fb, short br, short bg, short bb) {
    short id = -1;

    for (auto& pair : _pairs) {
        if (pair->_foreground->_r == fr && pair->_foreground->_g == fg && pair->_foreground->_b == fb &&
        pair->_background->_r == br && pair->_background->_g == bg && pair->_background->_b == bb) {
            id = pair->_id;
        }
    }

    if (id == -1) {
        Color* foreground = Color::get(fr, fg, fb);
        Color* background = Color::get(br, bg, bb);

        auto colorPair = new ColorPair(foreground, background);
        id = colorPair->_id;
    }

    wattron(win, COLOR_PAIR(id));
    wbkgd(win, COLOR_PAIR(id));
}
