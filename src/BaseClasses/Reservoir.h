#ifndef WATER_MANAGEMENT_RESERVOIR_H
#define WATER_MANAGEMENT_RESERVOIR_H

#include <string>
#include <unordered_map>
#include <unordered_set>

class Reservoir{
public:
    Reservoir(const std::string&, const std::string&, const int&, const std::string&, const int&);
    std::string getName() const;
    std::string getMunicipality() const;
    int getID() const;
    std::string getcode() const;
    int getMaxDelivery() const;

    struct ReservoirHash{
        size_t operator()(const Reservoir& reservoir) const
        {
            return std::hash<int>()(reservoir.getID());
        }
        bool operator()(const Reservoir& reservoir1,const Reservoir& reservoir2) const
        {
            return reservoir1.getID() == reservoir2.getID();
        }
    };
    typedef std::unordered_set<Reservoir, Reservoir::ReservoirHash, Reservoir::ReservoirHash> ReservoirH;
private:
    std::string name;
    std::string municipality;
    int id;
    std::string code;
    int maxDelivery;
};
#endif
