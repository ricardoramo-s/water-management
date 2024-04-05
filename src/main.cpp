#include "DataManagement/DataReader.h"
#include "GraphClasses/Graph.h"
#include "DataManagement/DataManager.h"
#include "test.h"



int main() {

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

    DataManager::edmondsKarp(&graph, graph.getSuperSource()->getCode(), graph.getSuperSink()->getCode());

    printSourceFlow(&graph);
    printSinkFlow(&graph);
}
