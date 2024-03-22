#ifndef WATER_MANAGEMENT_CITY_H
#define WATER_MANAGEMENT_CITY_H

#include <string>
#include <unordered_map>
#include <unordered_set>

class City{
public:
    City(const std::string&, const int&, const std::string&, const int&, const int&);
    std::string getName() const;
    int getID() const;
    std::string getcode() const;
    int getDemand() const;
    int getPopulation() const;

    struct CitiesHash{
        size_t operator()(const City& city) const
        {
            return std::hash<int>()(city.getID());
        }
        bool operator()(const City& city1, const City& city2) const
        {
            return city1.getID() == city2.getID();
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
