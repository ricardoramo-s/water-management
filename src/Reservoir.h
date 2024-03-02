#ifndef WATER_MANAGEMENT_RESERVOIR_H
#define WATER_MANAGEMENT_RESERVOIR_H

#include <string>
#include <unordered_map>
#include <unordered_set>

class Reservoir{
public:
    Reservoir(const std::string& name);
    Reservoir(const std::string&, const std::string&, const int&, const std::string&, const int&);
    std::string getName() const;
    std::string getMunicipality() const;
    int getID() const;
    std::string getcode() const;
    int getMaxDelivery() const;
    struct ReservoirHash{
        int operator()(const Reservoir& Reservoir) const{
            std::string c=Reservoir.getName();
            int v=0;
            for(char i:c){
                v=37*v+i;
            }
            return v;
        }
        bool operator()(const Reservoir& Reservoir1,const Reservoir& Reservoir2) const{
            return Reservoir1.getName() == Reservoir2.getName();
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
