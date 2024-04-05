#ifndef WATER_MANAGEMENT_SEARCHBOX_H
#define WATER_MANAGEMENT_SEARCHBOX_H

#include "ui/components/TextBox.h"
#include "ui/components/InputBox.h"
#include "vector"
#include "components/MultiComponent.h"

class SearchBox : public Component {
    MultiComponent<TextBox>* multi_text_box_;
    InputBox* input_box_;

    std::vector<std::vector<std::string>> options_;
    short highlighted_color_id_ = 0;

public:
    SearchBox(int height, int width, int y, int x);

    void add_options(std::vector<std::string>& options, std::string header);
    void set_highlighted_color(short id);

    std::string get_selected() const;

    void draw() override;
    void handle_input(int ch) override;

    void hide() const override;
    void show() const override;

    ~SearchBox() override;
};


#endif //WATER_MANAGEMENT_SEARCHBOX_H
