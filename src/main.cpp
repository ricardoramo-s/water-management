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

    DataManager::edmondsKarp(&graph);

    //printSourceFlow(&graph);
    //printSinkFlow(&graph);
    //graph.setEdgeUsing("PS_9", "PS_10", 1);
    //graph.setEdgeUsing("PS_4", "PS_5",  1);
    //graph.setVertexUsing("C_6", 0);
    //DataManager::edmondsKarp(&graph);
    //printSourceFlow(&graph);
    //printSinkFlow(&graph);
    //DataManager::resetUsing(&graph);
    //printFromAtoB(graph, "R_1", "C_5");
    //printEdges(&graph);
    //PathsVector pathsVector = exploreAllPaths(&graph);
    //printAllPaths(pathsVector);

    printEdges(&graph);

    balanceFlow(&graph);
    cout << "\n---------------------\n\n";

    printEdges(&graph);

}
