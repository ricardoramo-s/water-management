#include "BasicMetricsBuffer.h"
#include "pallets/gruvbox.h"
#include "components/KeysBindings.h"
#include "BalanceBuffer.h"


BasicMetricsBuffer::BasicMetricsBuffer() : Buffer() {
    set_color(ColorPair::get(light0, dark0));

    search_box_ = new SearchBox(get_height() - 8,  (get_width() - 16) / 2, 4, 8);
    std::vector<std::string> northMunicipalities = {"Alijó","Amares","Arcos de Valdevez","Barcelos","Boticas","Braga","Bragança","Cabeceiras de Basto","Caminha","Celorico de Basto","Chaves","Espinho","Esposende","Fafe","Felgueiras","Guimarães","Lamego","Lousada","Maia","Marco de Canaveses","Matosinhos","Melgaço","Mesão Frio","Mirandela","Mogadouro","Monção","Montalegre","Murça","Oliveira de Azeméis","Paços de Ferreira","Paredes","Paredes de Coura","Penafiel","Peso da Régua","Ponte da Barca","Ponte de Lima","Póvoa de Lanhoso","Póvoa de Varzim","Ribeira de Pena","Sabrosa","Santa Maria da Feira","Santo Tirso","São João da Madeira","Terras de Bouro","Trofa","Valença","Valongo","Valpaços","Viana do Castelo","Vieira do Minho","Vila do Conde","Vila Flor","Vila Nova de Cerveira","Vila Nova de Famalicão","Vila Nova de Foz Côa","Vila Nova de Gaia","Vila Nova de Paiva","Vila Pouca de Aguiar","Vila Real","Vimioso"};

    // TODO: fetch cities from graph
    search_box_->add_options(northMunicipalities, "City:");
    search_box_->set_color(ColorPair::get(light0, dark0));
    search_box_->set_highlighted_color(ColorPair::get(dark0, light0));
    search_box_->set_box_color(ColorPair::get(light0, dark0));
    search_box_->on_highlight([&] {
        balance_->set_color(ColorPair::get(light0, dark0));
        search_box_->set_box_color(ColorPair::get(bright_aqua, dark0));
    });

    id_ = new TextLabel(20, 4, get_width() / 2 + 8);
    id_->set_color(ColorPair::get(light0, dark0));

    code_ = new TextLabel(20, 6, get_width() / 2 + 10);
    code_->set_color(ColorPair::get(light0, dark0));

    demand_ = new TextLabel(20, 8, get_width() / 2 + 12);
    demand_->set_color(ColorPair::get(light0, dark0));

    population_ = new TextLabel(20, 10, get_width() / 2 + 16);
    population_->set_color(ColorPair::get(light0, dark0));

    balance_ = new TextLabel(11, get_height() * (2.5 / 4), get_width() * (3.0 / 4) - 4);
    balance_->set_text("> Balance <");
    balance_->set_color(ColorPair::get(light0, dark0));
    balance_->on_select([&] {
        next_buffer_ = balance_buffer_;
        next_buffer_->previous_buffer(this);
    });
    balance_->on_highlight([&] {
        balance_->set_color(ColorPair::get(dark0, light0));
        search_box_->set_box_color(ColorPair::get(light0, dark0));
    });

    search_box_->set_userptr(balance_);
    balance_->set_userptr(search_box_);

    currently_selected_component_ = search_box_;
    search_box_->highlight();

    balance_buffer_ = new BalanceBuffer();

    this->hide();
    this->set_color(ColorPair::get(light0, dark0));
}

void BasicMetricsBuffer::draw() {
    mvwprintw(get_win(), id_->get_y(), id_->get_x() - 4, "%s", "id:");
    mvwprintw(get_win(), code_->get_y(), code_->get_x() - 6, "%s", "Code:");
    mvwprintw(get_win(), demand_->get_y(), demand_->get_x() - 8, "%s", "Demand:");
    mvwprintw(get_win(), population_->get_y(), population_->get_x() - 12, "%s", "Population:");

    search_box_->draw();
    id_->draw();
    code_->draw();
    demand_->draw();
    population_->draw();
    balance_->draw();
}

void BasicMetricsBuffer::handle_input(int ch) {
    switch (ch) {
        case ESC:
            if (previous_buffer_ != nullptr) {
                next_buffer_ = previous_buffer_;
            }
            break;
        case TAB:
            select_component((Component*) currently_selected_component_->get_userptr());
            currently_selected_component_->highlight();
            break;
        default:
            currently_selected_component_->handle_input(ch);
    }

    std::string current_city = search_box_->get_selected();

    if (current_city.empty()) {
        id_->set_text("");
        code_->set_text("");
        demand_->set_text("");
        population_->set_text("");
    }
    else {
        id_->set_text(current_city);
        // TODO: get information from graph
    }
}

void BasicMetricsBuffer::hide() const {
    id_->hide();
    code_->hide();
    demand_->hide();
    population_->hide();
    search_box_->hide();
    balance_->hide();

    hide_panel(get_panel());
}

void BasicMetricsBuffer::show() const {
    show_panel(get_panel());

    id_->show();
    code_->show();
    demand_->show();
    population_->show();
    search_box_->show();
    balance_->show();
}

BasicMetricsBuffer::~BasicMetricsBuffer() {
    delete id_;
    delete code_;
    delete demand_;
    delete population_;
    delete search_box_;
    delete balance_;
}