#ifndef WATER_MANAGEMENT_CITY_H
#define WATER_MANAGEMENT_CITY_H

#include <string>
#include <unordered_map>

class City{
public:

    typedef std::unordered_map<int, City*> CitiesMap;

    City() = default;
    City(const std::string& name, const int& id, const std::string& code,
         const int& demand, const std::string& population);

    std::string getName() const;
    int getId() const;
    std::string getcode() const;
    int getDemand() const;
    std::string getPopulation() const;

    static void addCity(City*);
    static City* getCity(int id);

private:

    static CitiesMap citiesMap;

    std::string name;
    int id;
    std::string code;
    int demand;
    std::string population;

};

#endif
