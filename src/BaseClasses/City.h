#ifndef WATER_MANAGEMENT_CITY_H
#define WATER_MANAGEMENT_CITY_H

#include <string>
#include <unordered_map>

class City{
public:

    /**
     * @brief Type definition for a map of cities, mapping city codes to city objects.
     */
    typedef std::unordered_map<std::string, City*> CitiesMap; // code -> city

    City() = default;
    /**
     * @brief Constructor for the City class.
     *
     * Initializes a City object with the provided attributes.
     *
     * @param name The name of the city.
     * @param id The ID of the city.
     * @param code The code of the city.
     * @param demand The demand of the city.
     * @param population The population of the city.
     */
    City(std::string name, int id, std::string code,
         double demand, std::string population);

    /**
     * @brief not implemented
     */
    ~City();


    std::string getName() const;

    /**
     * @brief Gets the ID of the city.
     *
     * This method returns the ID of the city.
     *
     * @return The ID of the city.
     */
    int getId() const;

    /**
     * @brief Gets the code of the city.
     *
     * This method returns the code of the city.
     *
     * @return The code of the city.
     */
    std::string getCode() const;

    /**
     * @brief Gets the demand of the city.
     *
     * This method returns the demand of the city.
     *
     * @return The demand of the city.
     */
    double getDemand() const;

    /**
     * @brief Gets the population of the city.
     *
     * This method returns the population of the city.
     *
     * @return The population of the city.
     */
    std::string getPopulation() const;

    /**
     * @brief Gets the total flow into the city.
     *
     * This method calculates and returns the total flow into the city by summing up
     * the flow values of all incoming edges to the city's corresponding vertex in the graph.
     *
     * @return The total flow into the city.
     */
    double getFlow() const;

    /**
     * @brief Adds a new city to the map.
     *
     * This method adds a new city to the map of cities if it doesn't already exist.
     *
     * @param city A pointer to the city object to be added.
     * @return True if the city was successfully added, false if the city already exists in the map.
     * @complexity O(1)
     */
    static bool addCity(City* city);

    /**
    * @brief not implemented
    */
    static bool removeCity(City* city);

    /**
    * @brief Retrieves a city from the map using its code.
    *
    * This method retrieves a city from the map of cities based on its code.
    * @param code The code of the city to retrieve.
    * @return A pointer to the city object if found, nullptr if the city with the given code does not exist.
     * @complexity O(1)
    */
    static City* getCity(const std::string& code);

    /**
     * @brief Gets the map of cities.
     *
     * This method returns a copy of the map containing all cities, where each city is mapped to its code.
     *
     * @return A copy of the map of cities.
     */
    static CitiesMap getCitiesMap();

private:

    /**
    * @brief Map of cities, mapping city codes to city objects.
    */
    static CitiesMap citiesMap;

    /**
     * @brief The name of the city.
     */
    std::string name;

    /**
     * @brief The ID of the city.
     */
    int id;

    /**
     * @brief The code of the city.
     */
    std::string code;

    /**
     * @brief The demand of the city.
     */
    double demand;

    /**
     * @brief The population of the city.
     */
    std::string population;

};

#endif
