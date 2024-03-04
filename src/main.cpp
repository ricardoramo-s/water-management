#include <ncurses.h>
#include "components/TextBox.h"
#include "components/Box.h"
#include "components/TextLabel.h"
#include "components/InputLabel.h"
#include "pallets/gruvbox.h"
#include "colors/ColorPair.h"
#include <string>

int main() {
    initscr();
    curs_set(0);
    noecho();
    start_color();

    ColorPair::apply(stdscr, light0, dark0);
    clear();
    refresh();

    auto textLabel = new TextLabel(2, 20, "Test Label");
    auto textLabelBox = new Box<TextLabel>(textLabel);

    //std::string lorem("Lorem ipsum dolor sit amet, consectetur adipiscing elit. In placerat vitae dolor in aliquet. Vestibulum ac urna scelerisque, sollicitudin lorem nec, tincidunt odio. Proin euismod, neque sed pharetra consectetur, lorem diam vulputate est, quis ullamcorper est nisl at lectus. Nulla sagittis at diam vel feugiat. Morbi ac egestas elit. Nam at dignissim tortor. Fusce tempor aliquam feugiat. Suspendisse finibus massa in velit aliquet, sit amet porttitor justo congue.");

    auto strings = std::vector<std::string>({"RicardoAaaaaaaaaaaaaaaaaaaaaaa", "Alexandre", "Alves", "Ramos", "OLASDASDASD", "Airlines", "Supa kika", "LCD", "BOM DIA SENHOR PROFESSOR REI"});
    auto textBox = new TextBox(6, 30, 5, 20, strings, true);
    auto textBoxBox = new Box<TextBox>(textBox, "Lorem ipsum");

    auto inputLabel = new InputLabel(15, 2, 3, "> ");
    auto inputLabelBox = new Box<InputLabel>(inputLabel);

    do {
        inputLabelBox->draw();
        textBoxBox->draw();
        textLabelBox->draw();
        doupdate();

        textBoxBox->handle_input();
    } while (true);

    clear();

    endwin();
    return 0;
}
