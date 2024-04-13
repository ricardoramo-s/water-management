#include "ExportBuffer.h"
#include "colors/ColorPair.h"
#include "pallets/gruvbox.h"
#include "fstream"
#include "cmath"
#include "iostream"
#include "BaseClasses/City.h"

ExportBuffer::ExportBuffer() : Buffer()
{
    input_box_ = new InputBox(get_width() / 2, get_height() / 2 - 1, get_width() / 4, "❯ ");
    input_box_->set_header_("Export to file:");
    input_box_->set_color(ColorPair::get(light0, dark0));
    input_box_->set_box_color(ColorPair::get(light0, dark0));
    input_box_->on_select([&]
                          {
        std::string path;
        if ((path = export_data()).empty()) {
            create_output("Export successfull!");
            export_output_->set_color(ColorPair::get(bright_green, dark0));

            select_component(export_output_);
        }
        else {
            std::string error_text = "Error: Could not open file '" + path + "'.";
            create_output(error_text);
            export_output_->set_color(ColorPair::get(bright_red, dark0));
        }

        export_output_->show(); });
    input_box_->on_cancel([&]
                          { next_buffer_ = previous_buffer_; });

    create_output("");

    wbkgd(get_win(), COLOR_PAIR(ColorPair::get(light0, dark0)));
    this->set_color(ColorPair::get(light0, dark0));
    this->hide();
    this->on_select([&]
                    {
        input_box_->clear();
        select_component(input_box_);

        export_output_->hide(); });

    select_component(input_box_);

    next_buffer_ = nullptr;
    previous_buffer_ = nullptr;
}

void ExportBuffer::handle_input(int ch)
{
    currently_selected_component_->handle_input(ch);
}

void ExportBuffer::draw()
{
    input_box_->draw();
    export_output_->draw();
}

std::string ExportBuffer::export_data()
{
    std::ofstream outfile(input_box_->get_input_text().c_str());

    if (!outfile.is_open())
    {
        return input_box_->get_input_text();
    }

    // Write the header row
    outfile << "City,Code,Max_Flow\n";

    // Write data rows
    for (const auto &[code, city] : City::getCitiesMap())
    {
        outfile << city->getName() << "," << city->getCode() << "," << std::to_string((int)std::round(city->getFlow())) << "\n";
    }

    outfile.close(); // Close the file

    return "";
}

void ExportBuffer::create_output(std::string string)
{
    if (export_output_ != nullptr)
        delete export_output_;

    export_output_ = new TextLabel(get_height() / 2 + 3, (get_width() / 2) - (int)(string.size() / 2), string);
    export_output_->on_select([&]
                              { next_buffer_ = previous_buffer_; });
    export_output_->on_cancel([&]
                              { next_buffer_ = previous_buffer_; });
    export_output_->hide();
}

void ExportBuffer::hide() const
{
    hide_panel(get_panel());
    input_box_->hide();
    export_output_->hide();
}

void ExportBuffer::show() const
{
    show_panel(get_panel());
    input_box_->show();
}

ExportBuffer::~ExportBuffer()
{
    delete input_box_;
    delete export_output_;
}
