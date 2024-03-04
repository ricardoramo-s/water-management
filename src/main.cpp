#include <ncurses.h>
#include "components/TextBox.h"
#include "components/Box.h"
#include "components/TextLabel.h"
#include "components/InputLabel.h"
#include "components/SearchBox.h"
#include "pallets/gruvbox.h"
#include "colors/ColorPair.h"
#include <string>

int main() {
    initscr();
    curs_set(0);
    noecho();
    ESCDELAY = 1;
    start_color();

    ColorPair::apply(stdscr, light0, dark0);
    clear();
    refresh();

    std::vector<std::string> northMunicipalities = {"Alijó","Amares","Arcos de Valdevez","Barcelos","Boticas","Braga","Bragança","Cabeceiras de Basto","Caminha","Celorico de Basto","Chaves","Espinho","Esposende","Fafe","Felgueiras","Guimarães","Lamego","Lousada","Maia","Marco de Canaveses","Matosinhos","Melgaço","Mesão Frio","Mirandela","Mogadouro","Monção","Montalegre","Murça","Oliveira de Azeméis","Paços de Ferreira","Paredes","Paredes de Coura","Penafiel","Peso da Régua","Ponte da Barca","Ponte de Lima","Póvoa de Lanhoso","Póvoa de Varzim","Ribeira de Pena","Sabrosa","Santa Maria da Feira","Santo Tirso","São João da Madeira","Terras de Bouro","Trofa","Valença","Valongo","Valpaços","Viana do Castelo","Vieira do Minho","Vila do Conde","Vila Flor","Vila Nova de Cerveira","Vila Nova de Famalicão","Vila Nova de Foz Côa","Vila Nova de Gaia","Vila Nova de Paiva","Vila Pouca de Aguiar","Vila Real","Vimioso"};
    auto search_box = new SearchBox(20, 50, 5, 10, northMunicipalities);

    do {
        search_box->draw();
        doupdate();

        search_box->handle_input();
    } while (true);

    clear();

    endwin();
    return 0;
}
