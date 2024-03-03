#include "ColorPair.h"

short ColorPair::last_pair_ = 1;

std::vector<ColorPair*> ColorPair::pairs_ = std::vector<ColorPair*>();

ColorPair::ColorPair(Color* foreground, Color* background) : _id(last_pair_++), _foreground(foreground), _background(background) {
    init_pair(_id, _foreground->id_, _background->id_);
    pairs_.push_back(this);
}

short ColorPair::get(short fr, short fg, short fb, short br, short bg, short bb) {
    short id = -1;

    for (auto& pair : pairs_) {
        if (pair->_foreground->_r == fr && pair->_foreground->g_ == fg && pair->_foreground->b_ == fb &&
            pair->_background->_r == br && pair->_background->g_ == bg && pair->_background->b_ == bb) {
            id = pair->_id;
        }
    }

    if (id == -1) {
        Color* foreground = Color::get(fr, fg, fb);
        Color* background = Color::get(br, bg, bb);

        auto colorPair = new ColorPair(foreground, background);
        id = colorPair->_id;
    }

    return id;
}

short ColorPair::activate(WINDOW *win, short id) {
    wattron(win, COLOR_PAIR(id));
    wbkgdset(win, COLOR_PAIR(id));

    return id;
}

short ColorPair::deactivate(WINDOW *win, short id) {
    wattroff(win, COLOR_PAIR(id));

    return id;
}

short ColorPair::apply(WINDOW *win, short fr, short fg, short fb, short br, short bg, short bb) {
    short id = get(fr, fg, fb, br, bg, bb);
    return activate(win, id);
}
