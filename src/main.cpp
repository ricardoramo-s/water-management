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
#include "test/StaticGraph.h"



int main() {
    setlocale(LC_ALL, "");

    initscr();
    cbreak();
    curs_set(0);
    keypad(stdscr, true);
    noecho();
    ESCDELAY = 15;
    start_color();

    DataReader dataReader = DataReader("/Users/ricardoramos/CLionProjects/water-management/SmallDataSet", "_Madeira");

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

    StaticGraph::graph_ = &graph;

    graph.setEdgeUsing("PS_9", "PS_10", 0);
    graph.setEdgeUsing("PS_4", "PS_5",  0);



    DataManager::edmondsKarp(&graph);

    //printSourceFlow(&graph);
    //printSinkFlow(&graph);

    DataManager::resetUsing(&graph);

    DataManager::edmondsKarp(&graph);

    //printSourceFlow(&graph);
    //printSinkFlow(&graph);

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
            buffer->on_select();
        }
    }

    clear();

    endwin();
    return 0;
}
