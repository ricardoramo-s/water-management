#ifndef WATER_MANAGEMENT_PUMP_H
#define WATER_MANAGEMENT_PUMP_H

#include <string>
#include <unordered_map>

class Pump {

public:

    typedef std::unordered_map<std::string, Pump*> PumpsMap; //code -> pump

    Pump() = default;
    Pump(int id, std::string code);
    ~Pump();

    int getID() const;
    std::string getCode() const;

    static bool addPump(Pump* pump);
    static bool removePump(Pump* pump);
    static Pump* getPump(const std::string& code);
    static PumpsMap getPumpsMap();

private:

    static PumpsMap pumpsMap;

    int id;
    std::string code;
};


#endif //WATER_MANAGEMENT_PUMP_H
