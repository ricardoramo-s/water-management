#include "BasicMetricsBuffer.h"
#include "pallets/gruvbox.h"
#include "components/KeysBindings.h"
#include "BalanceBuffer.h"
#include "BaseClasses/City.h"
#include "cmath"

BasicMetricsBuffer::BasicMetricsBuffer() : Buffer(), balance_buffer_(nullptr), export_buffer_(nullptr)
{
    search_box_ = new SearchBox(get_height() - 8, (get_width() - 16) / 2, 4, 8);

    std::vector<std::string> cities;
    for (const auto &city : City::getCitiesMap())
    {
        cities.push_back(city.second->getName() + " #" + city.first);
    }

    search_box_->add_options(cities, "City:");
    search_box_->set_color(ColorPair::get(light0, dark0));
    search_box_->set_highlighted_color(ColorPair::get(dark0, light0));
    search_box_->set_box_color(ColorPair::get(light0, dark0));
    search_box_->on_highlight([&]
                              {
        export_->set_color(ColorPair::get(light0, dark0));
        search_box_->set_box_color(ColorPair::get(bright_aqua, dark0)); });

    max_flow_ = new TextLabel(20, 2, get_width() / 2 + 2);
    max_flow_->set_color(ColorPair::get(bright_blue, dark0));

    id_ = new TextLabel(20, 4, get_width() / 2 + 8);
    id_->set_color(ColorPair::get(light0, dark0));

    code_ = new TextLabel(20, 6, get_width() / 2 + 10);
    code_->set_color(ColorPair::get(light0, dark0));

    demand_ = new TextLabel(20, 8, get_width() / 2 + 12);
    demand_->set_color(ColorPair::get(light0, dark0));

    flow_ = new TextLabel(20, 10, get_width() / 2 + 10);
    flow_->set_color(ColorPair::get(light0, dark0));

    deficit_ = new TextLabel(20, 12, get_width() / 2 + 13);
    deficit_->set_color(ColorPair::get(light0, dark0));

    population_ = new TextLabel(20, 14, get_width() / 2 + 16);
    population_->set_color(ColorPair::get(light0, dark0));

    balance_ = new TextLabel(11, get_height() * (2.5 / 4) + 2, get_width() * (3.0 / 4) - 4);
    balance_->set_text("> Balance <");
    balance_->set_color(ColorPair::get(light0, dark0));
    balance_->on_highlight([&]
                           {
        search_box_->set_box_color(ColorPair::get(light0, dark0));
        balance_->set_color(ColorPair::get(dark0, light0)); });
    balance_->on_select([&]
                        { 
                            if (balance_buffer_ == nullptr) {
                                balance_buffer_ = new BalanceBuffer();
                                balance_buffer_->previous_buffer(this);
                            }
                            next_buffer_ = balance_buffer_; });

    balance_buffer_ = new BalanceBuffer();
    balance_buffer_->previous_buffer(this);

    export_ = new TextLabel(18, get_height() * (2.5 / 4) + 4, get_width() * (3.0 / 4) - 7);
    export_->set_text("> Export to file <");
    export_->set_color(ColorPair::get(light0, dark0));
    export_->on_highlight([&]
                          {
        balance_->set_color(ColorPair::get(light0, dark0));
        export_->set_color(ColorPair::get(dark0, light0)); });
    export_->on_select([&]
                       { 
                        if (export_buffer_ == nullptr) {
                            export_buffer_ = new ExportBuffer();
                            export_buffer_->previous_buffer(this);
                        }
                        next_buffer_ = export_buffer_; });

    search_box_->set_next_component(balance_);
    balance_->set_next_component(export_);
    export_->set_next_component(search_box_);

    currently_selected_component_ = search_box_;
    search_box_->highlight();

    this->hide();
    wbkgd(get_win(), COLOR_PAIR(ColorPair::get(light0, dark0)));
    this->set_color(ColorPair::get(light0, dark0));
    this->on_select([&]
                    {
        export_->on_highlight();
        search_box_->on_highlight();

        select_component(search_box_);
        read_city_data();

        max_flow_->set_text(std::to_string((int) std::round(get_max_flow()))); });
}

void BasicMetricsBuffer::draw()
{
    mvwprintw(get_win(), max_flow_->get_y(), max_flow_->get_x() - 10, "%s", "Max Flow:");
    mvwprintw(get_win(), id_->get_y(), id_->get_x() - 4, "%s", "id:");
    mvwprintw(get_win(), code_->get_y(), code_->get_x() - 6, "%s", "Code:");
    mvwprintw(get_win(), demand_->get_y(), demand_->get_x() - 8, "%s", "Demand:");
    mvwprintw(get_win(), flow_->get_y(), flow_->get_x() - 6, "%s", "Flow:");
    mvwprintw(get_win(), deficit_->get_y(), deficit_->get_x() - 9, "%s", "Deficit:");
    mvwprintw(get_win(), population_->get_y(), population_->get_x() - 12, "%s", "Population:");

    read_city_data();

    search_box_->draw();
    export_->draw();
    balance_->draw();

    max_flow_->draw();
    id_->draw();
    code_->draw();
    demand_->draw();
    flow_->draw();
    deficit_->draw();
    population_->draw();
}

void BasicMetricsBuffer::handle_input(int ch)
{
    switch (ch)
    {
    case ESC:
        if (previous_buffer_ != nullptr)
        {
            next_buffer_ = previous_buffer_;
        }
        break;
    case TAB:
        select_component(currently_selected_component_->get_next_component());
        currently_selected_component_->highlight();
        break;
    default:
        currently_selected_component_->handle_input(ch);
    }
}

void BasicMetricsBuffer::read_city_data()
{
    std::string current_city = search_box_->get_selected_string();

    if (current_city.empty())
    {
        id_->set_text("");
        code_->set_text("");
        demand_->set_text("");
        flow_->set_text("");
        deficit_->set_text("");
        population_->set_text("");
    }
    else
    {
        std::string code;

        auto hashPosition = current_city.find('#');
        if (hashPosition != std::string::npos)
        {
            code = current_city.substr(hashPosition + 1); // Extract the part after '#'
        }

        City *city = City::getCity(code);

        if (city)
        {
            id_->set_text(std::to_string(city->getId()));
            code_->set_text(city->getCode());
            demand_->set_text(std::to_string((int)std::round(city->getDemand())));
            flow_->set_text(std::to_string((int)std::round(city->getFlow())));
            double deficit = city->getDemand() - city->getFlow();

            if (deficit == 0)
            {
                deficit_->set_color(ColorPair::get(bright_green, dark0));
            }
            else
            {
                deficit_->set_color(ColorPair::get(bright_red, dark0));
            }
            deficit_->set_text(std::to_string((int)std::round(deficit)));
            population_->set_text(city->getPopulation());
        }
    }
}

double BasicMetricsBuffer::get_max_flow()
{
    double max_flow = 0;

    for (auto pair : City::getCitiesMap())
    {
        City *city = pair.second;

        max_flow += city->getFlow();
    }

    return max_flow;
}

void BasicMetricsBuffer::hide() const
{
    max_flow_->hide();
    id_->hide();
    code_->hide();
    demand_->hide();
    flow_->hide();
    deficit_->hide();
    population_->hide();

    search_box_->hide();
    export_->hide();
    balance_->hide();

    hide_panel(get_panel());
}

void BasicMetricsBuffer::show() const
{
    show_panel(get_panel());

    max_flow_->show();
    id_->show();
    code_->show();
    demand_->show();
    flow_->show();
    deficit_->show();
    population_->show();

    search_box_->show();
    export_->show();
    balance_->show();
}

BasicMetricsBuffer::~BasicMetricsBuffer()
{
    delete max_flow_;
    delete id_;
    delete code_;
    delete demand_;
    delete flow_;
    delete deficit_;
    delete population_;

    delete search_box_;
    delete balance_;
    delete export_;

    delete balance_buffer_;
    delete export_buffer_;
}
