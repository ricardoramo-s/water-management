#ifndef WATER_MANAGEMENT_RESERVOIR_H
#define WATER_MANAGEMENT_RESERVOIR_H

#include <string>
#include <unordered_map>

class Reservoir{
public:

    /**
     * @brief Type definition for a map of reservoirs, mapping reservoir codes to reservoir objects.
     */
    typedef std::unordered_map<std::string, Reservoir*> ReservoirsMap;

    /**
     * @brief Default constructor.
     */
    Reservoir() = default;

    /**
     * @brief Constructor with parameters.
     *
     * @param name The name of the reservoir.
     * @param municipality The municipality where the reservoir is located.
     * @param id The ID of the reservoir.
     * @param code The code of the reservoir.
     * @param maxDelivery The maximum delivery capacity of the reservoir.
     */
    Reservoir(std::string name, std::string municipality, int id, std::string code, double maxDelivery);

    /**
     * @brief not implemented.
     */
    ~Reservoir();

    /**
     * @brief Gets the name of the reservoir.
     *
     * @return The name of the reservoir.
     */
    std::string getName() const;

    /**
     * @brief Gets the municipality where the reservoir is located.
     *
     * @return The municipality of the reservoir.
     */
    std::string getMunicipality() const;

    /**
     * @brief Gets the ID of the reservoir.
     *
     * @return The ID of the reservoir.
     */
    int getID() const;

    /**
     * @brief Gets the code of the reservoir.
     *
     * @return The code of the reservoir.
     */
    std::string getCode() const;

    /**
     * @brief Gets the maximum delivery capacity of the reservoir.
     *
     * @return The maximum delivery capacity of the reservoir.
     */
    double getMaxDelivery() const;

    /**
     * @brief Adds a reservoir to the static reservoirs map.
     *
     * @param reservoir The reservoir to add.
     * @return True if the reservoir was added successfully, false otherwise.
     * @complexity O(1)
     */
    static bool addReservoir(Reservoir* reservoir);

    /**
     * @brief not implemented
     */
    static bool removeReservoir(Reservoir* reservoir);

    /**
     * @brief Retrieves a reservoir from the static reservoirs map based on its code.
     *
     * @param code The code of the reservoir to retrieve.
     * @return A pointer to the reservoir object if found, or nullptr if not found.
     * @complexity O(1)
     */
    static Reservoir* getReservoir(const std::string& code);

    /**
     * @brief Gets the static reservoirs map.
     *
     * @return The static reservoirs map.
     */
    static ReservoirsMap getReservoirsMap();


private:

    /**
    * @brief Static map of reservoirs, mapping reservoir codes to reservoir objects.
    */
    static ReservoirsMap reservoirsMap;

    /**
     * @brief The name of the reservoir.
     */
    std::string name;

    /**
     * @brief The municipality where the reservoir is located.
     */
    std::string municipality;

    /**
     * @brief The ID of the reservoir.
     */
    int id;

    /**
     * @brief The code of the reservoir.
     */
    std::string code;

    /**
     * @brief The maximum delivery capacity of the reservoir.
     */
    double maxDelivery;
};
#endif
