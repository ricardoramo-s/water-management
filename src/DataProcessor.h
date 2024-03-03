#ifndef WATER_MANAGEMENT_DATAPROCESSOR_H
#define WATER_MANAGEMENT_DATAPROCESSOR_H

#include <fstream>
#include <istream>
#include <sstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>

#include "Graph.h"

class DataProcessor{
public:

    DataProcessor();

    //getters
    PumpingStations::PumpingStationsH getPStations() const;
    std::unordered_map<std::string, int> getId() const;
    Graph getGraph() const;
    Graph getSubGraph() const;
    std::unordered_map<std::string, int> getSubGraphStations() const;

    void setSubGraph(const Graph& subgraph);

    //validate
    bool isStation(const std::string& station);
    bool isLine(const std::string& line);

    Graph originalGraph();

    Graph subgraph(const std::unordered_set<std::string>& failedLines);
    Graph subgraph(const std::vector<std::pair<std::string, std::string>>& failedSegments);
    Graph subgraph(const PumpingStations::PumpingStationsH& failedStations);

    std::vector<std::pair<std::string, int>> maxConnectedStations(int type);

    std::vector<std::pair<std::string, int>> flowDifference(const Graph& _subGraph);

    std::vector<std::pair<std::string, int>> transportNeeds(bool graphType, const Graph& graph, bool type);

    int finalStationFlow(const Graph& _graph, int target);

    int maxStationFlow(const std::string& station);

private:

    void createStations();
    void stationsFlow();

    //graph variants
    void createSuperSource(int id, PumpingStations::PumpingStationsH targetStations);
    void createSuperSink(int id, PumpingStations::PumpingStationsH targetStations);
    void createSuperGraph(bool type, const Graph& graph, const PumpingStations::PumpingStationsH& targetStations);
    void createSuperSourceGraph(bool type, const Graph& graph, int target);

    static void checkField(std::istringstream &iss, std::string &field);
    static std::string removeQuotes(std::istringstream &iss, std::string field);

    int makeVertex(Graph &_graph, std::unordered_map<std::string, int> &ids, const std::string &name, int &id);

    static bool segmentFailure(const std::vector<std::pair<std::string, std::string>>& failedSegments, const std::string& source, const std::string& target);
    bool lineFailure(std::unordered_set<std::string> failedLines, const std::string &source, const std::string &target);
    static bool stationFailure(PumpingStations::PumpingStationsH failedStations, const std::string &source, const std::string &target);

    PumpingStations::PumpingStationsH stations;
    std::unordered_map<std::string, int> PStations;

    std::unordered_map<std::string, Reservoir::ReservoirH> Reservoirs;
    std::unordered_map<std::string, City::CitiesH> Cities;

    std::unordered_map<std::string, int> subGraphStations;
    std::unordered_map<std::string, int> superGraphStations;

    std::unordered_set<std::string> edges;

    std::unordered_map<std::string, int> stationFlow;

    Graph graph;
    Graph subGraph;
    Graph superGraph;
};

#endif
