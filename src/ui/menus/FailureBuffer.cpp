#include "FailureBuffer.h"

#include "colors/ColorPair.h"
#include "BaseClasses/City.h"
#include "BaseClasses/Reservoir.h"
#include "BaseClasses/Pump.h"
#include "BaseClasses/Pipe.h"
#include "pallets/gruvbox.h"
#include "components/KeysBindings.h"
#include "DataManagement/DataManager.h"
#include "GraphClasses/StaticGraph.h"
#include "cmath"

FailureBuffer::FailureBuffer() : Buffer()
{
    std::vector<std::string> pumps, reservoirs, pipes, cities;

    for (const auto &[code, city] : City::getCitiesMap())
    {
        original_flow_.emplace(city, city->getFlow());
    }

    for (const auto &[code, reservoir] : Reservoir::getReservoirsMap())
    {
        reservoirs.push_back(reservoir->getName() + " #" + reservoir->getCode());
    }

    for (const auto &[code, pump] : Pump::getPumpsMap())
    {
        pumps.push_back("#" + pump->getCode());
    }

    for (const auto &[code, pipe] : Pipe::getPipesMultiMap().getPtCMAP())
    {
        pipes.push_back(pipe->getOrg() + " - " + pipe->getDest());
    }

    for (const auto &[code, pipe] : Pipe::getPipesMultiMap().getPtPMAP())
    {
        pipes.push_back(pipe->getOrg() + " - " + pipe->getDest());
    }

    for (const auto &[code, pipe] : Pipe::getPipesMultiMap().getRtPMAP())
    {
        pipes.push_back(pipe->getOrg() + " - " + pipe->getDest());
    }

    name_ = new TextLabel(10, get_height() / 2 + 2, get_width() / 2 + 8);
    name_->set_color(ColorPair::get(light0, dark0));
    name_->set_text("name");

    code_ = new TextLabel(10, get_height() / 2 + 2, get_width() - 11);
    code_->set_color(ColorPair::get(light0, dark0));
    code_->set_text("code");

    old_flow_ = new TextLabel(10, get_height() / 2 + 6, get_width() * (3.0 / 4) + 3);
    old_flow_->set_color(ColorPair::get(light0, dark0));
    old_flow_->set_text("oflow");

    new_flow_ = new TextLabel(10, get_height() / 2 + 8, get_width() * (3.0 / 4) + 3);
    new_flow_->set_color(ColorPair::get(light0, dark0));
    new_flow_->set_text("nflow");

    deficit_ = new TextLabel(10, get_height() / 2 + 10, get_width() * (3.0 / 4) + 2);
    deficit_->set_color(ColorPair::get(light0, dark0));
    deficit_->set_text("deficit");

    affected_cities_ = new TextBox(get_height() / 2, get_width() / 2 - 2, 1, get_width() / 2 + 1, true);
    affected_cities_->set_header_("Affected Cities");
    affected_cities_->set_color(ColorPair::get(light0, dark0));
    affected_cities_->set_box_color(ColorPair::get(light0, dark0));
    affected_cities_->set_highlighted_color(ColorPair::get(dark0, light0));
    affected_cities_->on_highlight([&]
                                   {
        on_maintenance_->select(-1);
        on_maintenance_->set_box_color(ColorPair::get(light0, dark0));
        affected_cities_->select(0);
        affected_cities_->set_box_color(ColorPair::get(bright_aqua, dark0)); });

    on_maintenance_ = new TextBox(get_height() * (1.0 / 3), get_width() / 2 - 2, 1, 2, true);
    on_maintenance_->set_header_("On Maintenance");
    on_maintenance_->set_color(ColorPair::get(light0, dark0));
    on_maintenance_->set_box_color(ColorPair::get(light0, dark0));
    on_maintenance_->set_highlighted_color(ColorPair::get(dark0, light0));
    on_maintenance_->on_select([&]
                               {
        std::string selected_string = on_maintenance_->get_selected_string();
        if (!selected_string.empty()) {
            on_maintenance_->remove();
            add_to_search_box(selected_string);
            update_flow();
        } });
    on_maintenance_->on_highlight([&]
                                  {
        search_box_->set_box_color(ColorPair::get(light0, dark0));
        on_maintenance_->select(0);
        on_maintenance_->set_box_color(ColorPair::get(bright_red, dark0)); });

    search_box_ = new SearchBox(get_height() * (2.0 / 3) - 1, get_width() / 2 - 2, get_height() * (1.0 / 3) + 1, 2);
    search_box_->add_options(reservoirs, "Reservoirs");
    search_box_->add_options(pumps, "Pumping Stations");
    search_box_->add_options(pipes, "Pipes");
    search_box_->set_color(ColorPair::get(light0, dark0));
    search_box_->set_box_color(ColorPair::get(light0, dark0));
    search_box_->set_highlighted_color(ColorPair::get(dark0, light0));
    search_box_->on_select([&]
                           {
        std::string selected_string = search_box_->get_selected_string();

        if (!selected_string.empty()) {
            add_to_maintenance(selected_string);
            search_box_->remove();
            update_flow();
        } });
    search_box_->on_highlight([&]
                              {
        affected_cities_->set_box_color(ColorPair::get(light0, dark0));
        search_box_->set_box_color(ColorPair::get(bright_aqua, dark0)); });

    search_box_->set_next_component(on_maintenance_);
    on_maintenance_->set_next_component(affected_cities_);
    affected_cities_->set_next_component(search_box_);

    wbkgd(get_win(), COLOR_PAIR(ColorPair::get(light0, dark0)));
    this->set_color(ColorPair::get(light0, dark0));
    this->hide();
    this->on_select([&]
                    {
        select_component(search_box_);
        search_box_->highlight();
        search_box_->clear(); });
}

void FailureBuffer::update_flow()
{
    DataManager::edmondsKarp(StaticGraph::graph_);

    std::vector<std::string> affected_cities;

    for (auto [city, old_flow] : original_flow_)
    {
        if (city->getFlow() != old_flow)
        {
            affected_cities.push_back(city->getName() + " #" + city->getCode());
        }
    }

    affected_cities_->set_lines_(affected_cities);
}

void FailureBuffer::read_city_data()
{
    std::string current_city = affected_cities_->get_selected_string();

    if (current_city.empty())
    {
        name_->set_text("");
        code_->set_text("");
        old_flow_->set_text("");
        new_flow_->set_text("");
        deficit_->set_text("");
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
            name_->set_text(city->getName());
            code_->set_text(city->getCode());

            double old_flow = original_flow_.at(city);
            old_flow_->set_text(std::to_string((int)std::round(old_flow)));
            new_flow_->set_text(std::to_string((int)std::round(city->getFlow())));
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
        }
    }
}

void FailureBuffer::add_to_search_box(std::string string)
{
    if (pipes_on_maintenance_.find(string) != pipes_on_maintenance_.end())
    {
        search_box_->add(2, string);
        pipes_on_maintenance_.erase(string);
        set_pipe_using(string, true);
    }
    if (pumps_on_maintenance_.find(string) != pumps_on_maintenance_.end())
    {
        search_box_->add(1, string);
        pumps_on_maintenance_.erase(string);
        set_pump_using(string, true);
    }
    if (reservoirs_on_maintenance_.find(string) != reservoirs_on_maintenance_.end())
    {
        search_box_->add(0, string);
        reservoirs_on_maintenance_.erase(string);
        set_reservoir_using(string, true);
    }
}

void FailureBuffer::add_to_maintenance(std::string string)
{
    on_maintenance_->add(string);

    if (search_box_->get_selected() == 0)
    {
        reservoirs_on_maintenance_.insert(string);
        set_reservoir_using(string, false);
    }
    else if (search_box_->get_selected() == 1)
    {
        pumps_on_maintenance_.insert(string);
        set_pump_using(string, false);
    }
    else
    {
        pipes_on_maintenance_.insert(string);
        set_pipe_using(string, false);
    }
}

void FailureBuffer::reset_manitenance()
{
    while (!pipes_on_maintenance_.empty())
    {
        add_to_search_box(*pipes_on_maintenance_.begin());
    }

    while (!reservoirs_on_maintenance_.empty())
    {
        add_to_search_box(*reservoirs_on_maintenance_.begin());
    }

    while (!pumps_on_maintenance_.empty())
    {
        add_to_search_box(*pumps_on_maintenance_.begin());
    }

    std::vector<std::string> empty;
    on_maintenance_->set_lines_(empty);
    update_flow();
}

void FailureBuffer::set_reservoir_using(std::string string, bool is_using)
{
    std::string code;
    auto hashPosition = string.find('#');
    if (hashPosition != std::string::npos)
    {
        code = string.substr(hashPosition + 1); // Extract the part after '#'
    }

    Vertex *vertex = StaticGraph::graph_->findVertex(code);
    vertex->setUsing(is_using);
}

void FailureBuffer::set_pump_using(std::string string, bool is_using)
{
    std::string code;
    code = string.substr(1);

    Vertex *vertex = StaticGraph::graph_->findVertex(code);
    vertex->setUsing(is_using);
}

void FailureBuffer::set_pipe_using(std::string string, bool is_using)
{
    // Find the positions of the spaces
    size_t first_space_pos = string.find(' ');
    size_t second_space_pos = string.find(' ', first_space_pos + 1);

    // Extract the substrings
    std::string source = string.substr(0, first_space_pos);
    std::string destination = string.substr(second_space_pos + 1);

    StaticGraph::graph_->setEdgeUsing(source, destination, is_using);
}

void FailureBuffer::handle_input(int ch)
{
    std::string selected;

    switch (ch)
    {
    case ESC:
        next_buffer_ = previous_buffer_;
        reset_manitenance();
        break;
    case TAB:
        select_component(currently_selected_component_->get_next_component());
        currently_selected_component_->on_highlight();
        break;
    default:
        currently_selected_component_->handle_input(ch);
    }
}

void FailureBuffer::draw()
{
    mvwprintw(get_win(), name_->get_y(), name_->get_x() - 6, "%s", "Name:");
    mvwprintw(get_win(), code_->get_y(), code_->get_x() - 6, "%s", "Code:");
    mvwprintw(get_win(), old_flow_->get_y(), old_flow_->get_x() - 10, "%s", "Old Flow:");
    mvwprintw(get_win(), new_flow_->get_y(), new_flow_->get_x() - 10, "%s", "New Flow:");
    mvwprintw(get_win(), deficit_->get_y(), deficit_->get_x() - 9, "%s", "Deficit:");

    read_city_data();

    affected_cities_->draw();
    on_maintenance_->draw();
    search_box_->draw();

    name_->draw();
    code_->draw();
    old_flow_->draw();
    new_flow_->draw();
    deficit_->draw();
}

void FailureBuffer::show() const
{
    show_panel(get_panel());

    affected_cities_->show();
    on_maintenance_->show();
    search_box_->show();

    name_->show();
    code_->show();
    old_flow_->show();
    new_flow_->show();
    deficit_->show();
}

void FailureBuffer::hide() const
{
    hide_panel(get_panel());

    affected_cities_->hide();
    on_maintenance_->hide();
    search_box_->hide();

    name_->hide();
    code_->hide();
    old_flow_->hide();
    new_flow_->hide();
    deficit_->hide();
}

FailureBuffer::~FailureBuffer()
{
    delete affected_cities_;
    delete on_maintenance_;
    delete search_box_;

    delete name_;
    delete code_;
    delete old_flow_;
    delete new_flow_;
    delete deficit_;
}
