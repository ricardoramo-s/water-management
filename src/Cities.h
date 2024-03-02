#ifndef WATER_MANAGEMENT_CITIES_H
#define WATER_MANAGEMENT_CITIES_H

#include <string>
#include <unordered_map>
#include <unordered_set>

class Cities{
public:
    Cities(const std::string& name);
    Cities(const std::string&, const int&, const std::string&, const int&, const int&);
    std::string getName() const;
    int getID() const;
    std::string getcode() const;
    int getDemand() const;
    int getPopulation() const;

    struct CitiesHash{
        int operator()(const Cities& Cities) const
        {
            std::string c=Cities.getName();
            int v=0;
            for(char i:c)
                v=37*v+i;
            return v;
        }
        bool operator()(const Cities& Cities1,const Cities& Cities2) const
        {
            return Cities1.getName() == Cities2.getName();
        }
    };
    typedef std::unordered_set<Cities, Cities::CitiesHash, Cities::CitiesHash> CitiesH;
private:
    std::string name;
    int id;
    std::string code;
    int demand;
    int population;
};

#endif
