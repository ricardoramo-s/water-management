#include <ncurses.h>
#include "ui/components/TextBox.h"
#include "ui/components/Box.h"
#include "ui/components/TextLabel.h"
#include "ui/components/InputLabel.h"
#include "ui/pallets/gruvbox.h"
#include "ui/colors/ColorPair.h"
#include <string>

int main() {
    initscr();
    curs_set(0);
    noecho();
    start_color();

    ColorPair::apply(stdscr, light0, dark0);
    refresh();

    auto textLabel = new TextLabel(2, 20, "Test Label");
    auto textLabelBox = new Box<TextLabel>(textLabel);

    std::string lorem("Lorem ipsum dolor sit amet, consectetur adipiscing elit. In placerat vitae dolor in aliquet. Vestibulum ac urna scelerisque, sollicitudin lorem nec, tincidunt odio. Proin euismod, neque sed pharetra consectetur, lorem diam vulputate est, quis ullamcorper est nisl at lectus. Nulla sagittis at diam vel feugiat. Morbi ac egestas elit. Nam at dignissim tortor. Fusce tempor aliquam feugiat. Suspendisse finibus massa in velit aliquet, sit amet porttitor justo congue.");

    auto textBox = new TextBox(30, 5, 20, lorem);
    auto textBoxBox = new Box<TextBox>(textBox, "Lorem ipsum");

    auto inputLabel = new InputLabel(15, 2, 3, "> ");
    auto inputLabelBox = new Box<InputLabel>(inputLabel);

    do {
        inputLabelBox->handle_input();
        inputLabelBox->draw();

        textBoxBox->draw();
        textLabelBox->draw();

        doupdate();
    } while (!inputLabel->get_input_flag());

    clear();

    endwin();
    return 0;
}
