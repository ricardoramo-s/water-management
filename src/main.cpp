#include "colors/ColorPair.h"
#include "menus/Buffer.h"
#include "menus/MainBuffer.h"

#include "DataManagement/DataReader.h"
#include "DataManagement/DataManager.h"
#include "GraphClasses/Graph.h"
#include "GraphClasses/StaticGraph.h"

#include <curses.h>
#include <clocale>
#include <string>

int main()
{
    setlocale(LC_ALL, "");

    initscr();
    start_color();
    curs_set(0);
    keypad(stdscr, true);
    noecho();
    ESCDELAY = 15;

    bool sucess = true;

    try
    {
        DataReader dataReader = DataReader("../Data", "");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        sucess = false;
    }

    if (!sucess)
    {
        try
        {
            DataReader dataReader = DataReader("./Data", "");
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    Graph graph;

    try
    {
        graph = DataManager::buildGraph();
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    StaticGraph::graph_ = &graph;
    DataManager::resetUsing(&graph);
    DataManager::edmondsKarp(&graph);

    Buffer *buffer;

    buffer = new MainBuffer();
    buffer->show();

    while (!buffer->to_quit())
    {
        clear();

        buffer->draw();
        update_panels();
        doupdate();

        buffer->handle_input(getch());
        Buffer *next_buffer = buffer->get_next_buffer();

        if (next_buffer != nullptr)
        {
            buffer->hide();
            buffer = (Buffer *)next_buffer;
            buffer->show();
            buffer->on_select();
        }
    }

    delete buffer;

    echo();
    noraw();
    keypad(stdscr, false);
    curs_set(1);
    endwin();
    return 0;
}
