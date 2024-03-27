#ifndef WATER_MANAGEMENT_PUMP_H
#define WATER_MANAGEMENT_PUMP_H

#include <string>
#include <unordered_set>

class Pump {

public:
    Pump(const int &id, const std::string &code);
    int getID() const;
    std::string getCode() const;

    struct StationHash{
        size_t operator()(const Pump& station) const
        {
            return std::hash<int>()(station.getID());
        }
        bool operator()(const Pump& station1, const Pump& station2) const
        {
            return station1.getID() == station2.getID();
        }
    };
    typedef std::unordered_set<Pump, Pump::StationHash, Pump::StationHash> PumpH;



private:
    int id;
    std::string code;
};


#endif //WATER_MANAGEMENT_PUMP_H
