#include "Menu.h"
#include "ncurses.h"
#include "colors/ColorPair.h"
#include "pallets/gruvbox.h"

Menu::Menu() {
    getmaxyx(stdscr, height_, width_);
}
