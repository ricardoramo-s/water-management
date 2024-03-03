#ifndef WATER_MANAGEMENT_CITY_H
#define WATER_MANAGEMENT_CITY_H

#include <string>
#include <unordered_map>
#include <unordered_set>

class City{
public:
    City(const std::string& name);
    City(const std::string&, const int&, const std::string&, const int&, const int&);
    std::string getName() const;
    int getID() const;
    std::string getcode() const;
    int getDemand() const;
    int getPopulation() const;

    struct CitiesHash{
        int operator()(const City& Cities) const
        {
            std::string c=Cities.getName();
            int v=0;
            for(char i:c)
                v=37*v+i;
            return v;
        }
        bool operator()(const City& Cities1, const City& Cities2) const
        {
            return Cities1.getName() == Cities2.getName();
        }
    };
    typedef std::unordered_set<City, City::CitiesHash, City::CitiesHash> CitiesH;
private:
    std::string name;
    int id;
    std::string code;
    int demand;
    int population;
};

#endif
