#ifndef WATER_MANAGEMENT_STATION_H
#define WATER_MANAGEMENT_STATION_H

#include <string>
#include <unordered_set>

class Station {

public:
    Station(const int &id, const std::string &code);
    int getID() const;
    std::string getCode() const;

    struct StationHash{
        size_t operator()(const Station& station) const
        {
            return std::hash<int>()(station.getID());
        }
        bool operator()(const Station& station1,const Station& station2) const
        {
            return station1.getID() == station2.getID();
        }
    };
    typedef std::unordered_set<Station, Station::StationHash, Station::StationHash> StationH;



private:
    int id;
    std::string code;
};


#endif //WATER_MANAGEMENT_STATION_H
