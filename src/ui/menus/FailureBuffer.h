#ifndef WATER_MANAGEMENT_FAILUREBUFFER_H
#define WATER_MANAGEMENT_FAILUREBUFFER_H

#include "unordered_set"
#include "components/TextBox.h"
#include "components/SearchBox.h"
#include "components/TextLabel.h"
#include "BaseClasses/City.h"
#include "Buffer.h"

class FailureBuffer : public Buffer {
private:
    TextBox *affected_cities_, *on_maintenance_;
    SearchBox *search_box_;
    TextLabel *name_, *code_ , *old_flow_, *new_flow_, *deficit_;

    std::unordered_set<std::string> pumps_on_maintenance_, pipes_on_maintenance_, reservoirs_on_maintenance_;
    std::unordered_map<City*, double> original_flow_;

    void update_flow();
    void read_city_data();
    void add_to_search_box(std::string string);
    void add_to_maintenance(std::string string);
    void reset_manitenance();

    void set_reservoir_using(std::string string, bool is_using);
    void set_pump_using(std::string string, bool is_using);
    void set_pipe_using(std::string string, bool is_using);
public:
    FailureBuffer();

    void draw() override;
    void handle_input(int ch) override;

    void hide() const override;
    void show() const override;

    ~FailureBuffer() override;
};


#endif //WATER_MANAGEMENT_FAILUREBUFFER_H
