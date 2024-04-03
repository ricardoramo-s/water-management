#ifndef WATER_MANAGEMENT_CITY_H
#define WATER_MANAGEMENT_CITY_H

#include <string>
#include <unordered_map>

class City{
public:

    typedef std::unordered_map<std::string, City*> CitiesMap; // code -> city

    City() = default;
    City(std::string name, int id, std::string code,
         int demand, std::string population);
    ~City();

    std::string getName() const;
    int getId() const;
    std::string getcode() const;
    int getDemand() const;
    std::string getPopulation() const;

    static bool addCity(City* city);
    static bool removeCity(City* city);
    static City* getCity(const std::string& code);

private:

    static CitiesMap citiesMap;

    std::string name;
    int id = NULL;
    std::string code;
    int demand = NULL;
    std::string population;

};

#endif
