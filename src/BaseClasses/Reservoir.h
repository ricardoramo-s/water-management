#ifndef WATER_MANAGEMENT_RESERVOIR_H
#define WATER_MANAGEMENT_RESERVOIR_H

#include <string>
#include <unordered_map>

class Reservoir{
public:

    typedef std::unordered_map<std::string, Reservoir*> ReservoirsMap;

    Reservoir() = default;
    Reservoir(std::string name, std::string municipality, int id, std::string code, double maxDelivery);
    ~Reservoir();

    std::string getName() const;
    std::string getMunicipality() const;
    int getID() const;
    std::string getcode() const;
    double getMaxDelivery() const;

    static bool addReservoir(Reservoir* reservoir);
    static bool removeReservoir(Reservoir* reservoir);
    static Reservoir* getReservoir(const std::string& code);
    static ReservoirsMap getReservoirsMap();

private:

    static ReservoirsMap reservoirsMap;

    std::string name;
    std::string municipality;
    int id;
    std::string code;
    double maxDelivery;
};
#endif
