//
// Created by Ricardo Ramos on 16/03/2024.
//

#include "Cmdline.h"
#include "colors/ColorPair.h"
#include "pallets/gruvbox.h"

Cmdline::Cmdline() : InputBox(60, 5, (getmaxx(stdscr) - 60) / 2, "❯ ") {
    set_header_("Cmdline");
    set_color(ColorPair::get(bright_red, dark0));
    set_box_color(ColorPair::get(bright_blue, dark0));
    on_select([&] {
        if (get_input_text() == "q") {
            system("clear");
            exit(0);
        }
        else {
            current_menu_->call_command(get_input_text());
        }
    });
    on_cancel([&] {
        current_menu_->select_previous_component();
        clear();
        hide();
    });
    hide();
}

void Cmdline::set_current_menu(Buffer *menu) {
    current_menu_ = menu;
}