#include <ncurses.h>
#include "components/TextBox.h"
#include "components/TextLabel.h"
#include "components/InputBox.h"
#include "ui/components/SearchBox.h"
#include "components/OptionMenu.h"
#include "components/KeysBindings.h"
#include "pallets/gruvbox.h"
#include "colors/ColorPair.h"
#include "menus/Buffer.h"
#include "menus/BasicMetricsBuffer.h"
#include "menus/BalanceBuffer.h"
#include "clocale"
#include <string>
#include "menus/MainBuffer.h"
#include "DataManagement/DataReader.h"
#include "GraphClasses/Graph.h"
#include "DataManagement/DataManager.h"
#include "test.h"



int main() {
    setlocale(LC_ALL, "");

    initscr();
    cbreak();
    curs_set(0);
    keypad(stdscr, true);
    noecho();
    ESCDELAY = 15;
    start_color();

    DataReader dataReader = DataReader(R"(C:\Users\bruno\Ambiente de Trabalho\Projects\water-management\SmallDataSet)", "_Madeira");

    City::CitiesMap citiesMap = City::getCitiesMap();

    //printCities();
    //printReservoirs();
    //printPumps();
    //printPipes();

    Graph graph;

    try {
        graph = DataManager::buildGraph();
    } catch (const std::runtime_error& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    graph.setEdgeUsing("PS_9", "PS_10", 0);
    graph.setEdgeUsing("PS_4", "PS_5",  0);



    DataManager::edmondsKarp(&graph);

    printSourceFlow(&graph);
    printSinkFlow(&graph);

    DataManager::resetUsing(&graph);

    DataManager::edmondsKarp(&graph);

    printSourceFlow(&graph);
    printSinkFlow(&graph);

    std::vector<std::string> northMunicipalities = {"Alijó","Amares","Arcos de Valdevez","Barcelos","Boticas","Braga","Bragança","Cabeceiras de Basto","Caminha","Celorico de Basto","Chaves","Espinho","Esposende","Fafe","Felgueiras","Guimarães","Lamego","Lousada","Maia","Marco de Canaveses","Matosinhos","Melgaço","Mesão Frio","Mirandela","Mogadouro","Monção","Montalegre","Murça","Oliveira de Azeméis","Paços de Ferreira","Paredes","Paredes de Coura","Penafiel","Peso da Régua","Ponte da Barca","Ponte de Lima","Póvoa de Lanhoso","Póvoa de Varzim","Ribeira de Pena","Sabrosa","Santa Maria da Feira","Santo Tirso","São João da Madeira","Terras de Bouro","Trofa","Valença","Valongo","Valpaços","Viana do Castelo","Vieira do Minho","Vila do Conde","Vila Flor","Vila Nova de Cerveira","Vila Nova de Famalicão","Vila Nova de Foz Côa","Vila Nova de Gaia","Vila Nova de Paiva","Vila Pouca de Aguiar","Vila Real","Vimioso"};
    std::vector<std::string> northReservoirs = {"Alto Rabagão", "Albufeira da Aguieira", "Albufeira do Azibo", "Albufeira da Baga", "Albufeira do Bemposta", "Albufeira do Cabril", "Albufeira do Carrapatelo", "Albufeira do Castelo de Bode", "Albufeira da Coa", "Albufeira do Douro Internacional", "Albufeira do Feiticeiro", "Albufeira da Foz Tua", "Albufeira do Fratel", "Albufeira da Grama", "Albufeira da Guadiana", "Albufeira do Lindoso", "Albufeira do Maranhão", "Albufeira do Miranda", "Albufeira do Monte da Rocha", "Albufeira do Ocreza", "Albufeira da Paradela", "Albufeira do Picote", "Albufeira do Pinhão", "Albufeira do Pocinho", "Albufeira da Ponte da Barca", "Albufeira da Salamonde", "Albufeira do Sabor", "Albufeira do São João da Pesqueira", "Albufeira do Torrão", "Albufeira do Vilarinho das Furnas", "Albufeira do Vírgenes"};
    Buffer* buffer;

    buffer = new MainBuffer();
    buffer->show();
    buffer->set_color(ColorPair::get(light0, dark0));

    while (true) {
        clear();

        buffer->draw();
        update_panels();
        doupdate();

        buffer->handle_input(getch());
        Buffer* next_buffer = buffer->get_next_buffer();

        if (next_buffer != nullptr) {
            buffer->hide();
            buffer = next_buffer;
            buffer->show();
        }
    }

    clear();

    endwin();
    return 0;
}
