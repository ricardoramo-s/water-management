#ifndef WATER_MANAGEMENT_PUMP_H
#define WATER_MANAGEMENT_PUMP_H

#include <string>
#include <unordered_map>


class Pump {

public:

    /**
     * @brief Type definition for a map of pumps, mapping pump codes to pump objects.
     */
    typedef std::unordered_map<std::string, Pump*> PumpsMap; //code -> pump

    /**
     * @brief Default constructor.
     */
    Pump() = default;

    /**
     * @brief Constructor with parameters.
     *
     * @param id The ID of the pump.
     * @param code The code of the pump.
     */
    Pump(int id, std::string code);

    /**
     * @brief not implemented.
     */
    ~Pump();

    /**
     * @brief Gets the ID of the pump.
     *
     * @return The ID of the pump.
     */
    int getID() const;

    /**
     * @brief Gets the code of the pump.
     *
     * @return The code of the pump.
     */
    std::string getCode() const;

    /**
     * @brief Adds a pump to the static pumps map.
     *
     * @param pump The pump to add.
     * @return True if the pump was added successfully, false otherwise.
     * @complexity O(1)
     */
    static bool addPump(Pump* pump);

    /**
     * @brief not implemented
     */
    static bool removePump(Pump* pump);

    /**
     * @brief Retrieves a pump from the static pumps map based on its code.
     *
     * @param code The code of the pump to retrieve.
     * @return A pointer to the pump object if found, or nullptr if not found.
     * @complexity O(1)
     */
    static Pump* getPump(const std::string& code);

    /**
     * @brief Gets the static pumps map.
     *
     * @return The static pumps map.
     */
    static PumpsMap getPumpsMap();

private:

    /**
     * @brief Static map of pumps, mapping pump codes to pump objects.
     */
    static PumpsMap pumpsMap;

    /**
     * @brief The ID of the pump.
     */
    int id;

    /**
     * @brief The code of the pump.
     */
    std::string code;
};


#endif //WATER_MANAGEMENT_PUMP_H
