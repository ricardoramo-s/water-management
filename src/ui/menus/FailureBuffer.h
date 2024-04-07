#ifndef WATER_MANAGEMENT_FAILUREBUFFER_H
#define WATER_MANAGEMENT_FAILUREBUFFER_H

#include "unordered_set"
#include "components/TextBox.h"
#include "components/SearchBox.h"
#include "components/TextLabel.h"
#include "BaseClasses/City.h"
#include "Buffer.h"

/**
 * @class FailureBuffer
 * @brief A class that represents a failure buffer.
 *
 * This class is derived from the Buffer class and it is used to manage the failure buffer.
 */
class FailureBuffer : public Buffer {
private:
    /**
     * @brief A pointer to a TextBox object representing affected cities.
     */
    TextBox *affected_cities_;

    /**
     * @brief A pointer to a TextBox object representing maintenance status.
     */
    TextBox *on_maintenance_;

    /**
     * @brief A pointer to a SearchBox object.
     */
    SearchBox *search_box_;

    /**
     * @brief A pointer to a TextLabel object representing the name.
     */
    TextLabel *name_;

    /**
     * @brief A pointer to a TextLabel object representing the code.
     */
    TextLabel *code_;

    /**
     * @brief A pointer to a TextLabel object representing the old flow.
     */
    TextLabel *old_flow_;

    /**
     * @brief A pointer to a TextLabel object representing the new flow.
     */
    TextLabel *new_flow_;

    /**
     * @brief A pointer to a TextLabel object representing the deficit.
     */
    TextLabel *deficit_;

    /**
     * @brief A set of strings representing pumps on maintenance.
     */
    std::unordered_set<std::string> pumps_on_maintenance_;

    /**
     * @brief A set of strings representing pipes on maintenance.
     */
    std::unordered_set<std::string> pipes_on_maintenance_;

    /**
     * @brief A set of strings representing reservoirs on maintenance.
     */
    std::unordered_set<std::string> reservoirs_on_maintenance_;

    /**
     * @brief A map of City pointers and their original flow.
     */
    std::unordered_map<City*, double> original_flow_;

    /**
     * @brief Updates the flow.
     */
    void update_flow();

    /**
     * @brief Reads city data.
     */
    void read_city_data();

    /**
     * @brief Adds a string to the search box.
     * @param string The string to be added.
     */
    void add_to_search_box(std::string string);

    /**
     * @brief Adds a string to the maintenance.
     * @param string The string to be added.
     */
    void add_to_maintenance(std::string string);

    /**
     * @brief Resets the maintenance.
     */
    void reset_manitenance();

    /**
     * @brief Sets the reservoir usage.
     * @param string The string representing the reservoir.
     * @param is_using The usage status of the reservoir.
     */
    void set_reservoir_using(std::string string, bool is_using);

    /**
     * @brief Sets the pump usage.
     * @param string The string representing the pump.
     * @param is_using The usage status of the pump.
     */
    void set_pump_using(std::string string, bool is_using);

    /**
     * @brief Sets the pipe usage.
     * @param string The string representing the pipe.
     * @param is_using The usage status of the pipe.
     */
    void set_pipe_using(std::string string, bool is_using);
public:
    /**
     * @brief Default constructor.
     */
    FailureBuffer();

    /**
     * @brief Draws the failure buffer.
     */
    void draw() override;

    /**
     * @brief Handles input events.
     * @param ch The character representing the input event.
     */
    void handle_input(int ch) override;

    /**
     * @brief Hides the failure buffer.
     */
    void hide() const override;

    /**
     * @brief Shows the failure buffer.
     */
    void show() const override;

    /**
     * @brief Default destructor.
     */
    ~FailureBuffer() override;
};


#endif //WATER_MANAGEMENT_FAILUREBUFFER_H
