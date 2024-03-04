#ifndef WATER_MANAGEMENT_TEXTBOX_H
#define WATER_MANAGEMENT_TEXTBOX_H

#include "Component.h"
#include "string"

class TextBox : public Component {
private:
    std::vector<std::string> lines_;

    int selected_ = -1, max_ = 0, min_ = 0;
    bool reversed_ = false;

    void check_bounds();

    void set_min_(int min);
    void set_max_(int max);
    void shift_window_down();
    void shift_window_up();

public:
    TextBox(int width, int y, int x, std::string& text);
    TextBox(int y, int x, std::vector<std::string>& lines);
    TextBox(int height, int width, int y, int x, std::vector<std::string>& lines, bool reversed);

    std::vector<std::string> get_lines_();
    void set_lines_(std::vector<std::string>& lines);

    std::string get_selected_string() const;
    int get_selected() const;

    void select(int i);
    void select(std::string& text);


    void draw() override;
    void handle_input() override;
    void handle_input(int ch);
};


#endif //WATER_MANAGEMENT_TEXTBOX_H
