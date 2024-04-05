#ifndef WATER_MANAGEMENT_CITY_H
#define WATER_MANAGEMENT_CITY_H

#include <string>
#include <unordered_map>

class City{
public:

    typedef std::unordered_map<std::string, City*> CitiesMap; // code -> city

    City() = default;
    City(std::string name, int id, std::string code,
         double demand, std::string population);
    ~City();

    std::string getName() const;
    int getId() const;
    std::string getCode() const;
    double getDemand() const;
    std::string getPopulation() const;

    static bool addCity(City* city);
    static bool removeCity(City* city);
    static City* getCity(const std::string& code);
    static CitiesMap getCitiesMap();

private:

    static CitiesMap citiesMap;

    std::string name;
    int id;
    std::string code;
    double demand;
    std::string population;

};

#endif
