#include <ncurses.h>
#include "components/TextBox.h"
#include "components/Box.h"
#include "components/TextLabel.h"
#include "components/InputBox.h"
#include "components/SearchBox.h"
#include "components/OptionMenu.h"
#include "components/KeysBindings.h"
#include "pallets/gruvbox.h"
#include "colors/ColorPair.h"
#include "menus/ReservoirMenu.h"
#include "locale.h"
#include <string>

int main() {
    setlocale(LC_ALL, "");

    initscr();
    curs_set(0);
    keypad(stdscr, true);
    noecho();
    ESCDELAY = 1;
    start_color();

    ColorPair::apply(stdscr, light0, dark0);
    clear();
    refresh();

    std::vector<std::string> northMunicipalities = {"Alijó","Amares","Arcos de Valdevez","Barcelos","Boticas","Braga","Bragança","Cabeceiras de Basto","Caminha","Celorico de Basto","Chaves","Espinho","Esposende","Fafe","Felgueiras","Guimarães","Lamego","Lousada","Maia","Marco de Canaveses","Matosinhos","Melgaço","Mesão Frio","Mirandela","Mogadouro","Monção","Montalegre","Murça","Oliveira de Azeméis","Paços de Ferreira","Paredes","Paredes de Coura","Penafiel","Peso da Régua","Ponte da Barca","Ponte de Lima","Póvoa de Lanhoso","Póvoa de Varzim","Ribeira de Pena","Sabrosa","Santa Maria da Feira","Santo Tirso","São João da Madeira","Terras de Bouro","Trofa","Valença","Valongo","Valpaços","Viana do Castelo","Vieira do Minho","Vila do Conde","Vila Flor","Vila Nova de Cerveira","Vila Nova de Famalicão","Vila Nova de Foz Côa","Vila Nova de Gaia","Vila Nova de Paiva","Vila Pouca de Aguiar","Vila Real","Vimioso"};
    std::vector<std::string> northReservoirs = {"Alto Rabagão", "Albufeira da Aguieira", "Albufeira do Azibo", "Albufeira da Baga", "Albufeira do Bemposta", "Albufeira do Cabril", "Albufeira do Carrapatelo", "Albufeira do Castelo de Bode", "Albufeira da Coa", "Albufeira do Douro Internacional", "Albufeira do Feiticeiro", "Albufeira da Foz Tua", "Albufeira do Fratel", "Albufeira da Grama", "Albufeira da Guadiana", "Albufeira do Lindoso", "Albufeira do Maranhão", "Albufeira do Miranda", "Albufeira do Monte da Rocha", "Albufeira do Ocreza", "Albufeira da Paradela", "Albufeira do Picote", "Albufeira do Pinhão", "Albufeira do Pocinho", "Albufeira da Ponte da Barca", "Albufeira da Salamonde", "Albufeira do Sabor", "Albufeira do São João da Pesqueira", "Albufeira do Torrão", "Albufeira do Vilarinho das Furnas", "Albufeira do Vírgenes"};

    auto search_box = new SearchBox(13, 30, 10, 10);
    //search_box->add_options(northMunicipalities, "Cities");
    //search_box->add_options(northReservoirs, "Reservoirs");

    /*
    auto text_box = new TextBox(10, 30, 2, 2, false);
    text_box->set_lines_(northMunicipalities);
    auto multi_component = new MultiComponent<TextBox>();
    multi_component->add_component(text_box);
    */

    do {
        search_box->draw();
        doupdate();
        search_box->handle_input(getch());
    } while (true);

    clear();

    endwin();
    return 0;
}
