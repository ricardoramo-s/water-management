#include "ReservoirBuffer.h"
#include "components/KeysBindings.h"
#include "colors/ColorPair.h"
#include "pallets/gruvbox.h"

ReservoirBuffer::ReservoirBuffer(Cmdline* cmdline) : Buffer(cmdline) {
    bool even_height = get_height() % 2 == 0;
    bool even_width = get_width() % 2 == 0;

    std::vector<std::string> northMunicipalities = {"Alijó","Amares","Arcos de Valdevez","Barcelos","Boticas","Braga","Bragança","Cabeceiras de Basto","Caminha","Celorico de Basto","Chaves","Espinho","Esposende","Fafe","Felgueiras","Guimarães","Lamego","Lousada","Maia","Marco de Canaveses","Matosinhos","Melgaço","Mesão Frio","Mirandela","Mogadouro","Monção","Montalegre","Murça","Oliveira de Azeméis","Paços de Ferreira","Paredes","Paredes de Coura","Penafiel","Peso da Régua","Ponte da Barca","Ponte de Lima","Póvoa de Lanhoso","Póvoa de Varzim","Ribeira de Pena","Sabrosa","Santa Maria da Feira","Santo Tirso","São João da Madeira","Terras de Bouro","Trofa","Valença","Valongo","Valpaços","Viana do Castelo","Vieira do Minho","Vila do Conde","Vila Flor","Vila Nova de Cerveira","Vila Nova de Famalicão","Vila Nova de Foz Côa","Vila Nova de Gaia","Vila Nova de Paiva","Vila Pouca de Aguiar","Vila Real","Vimioso"};
    std::vector<std::string> northReservoirs = {"Alto Rabagão", "Albufeira da Aguieira", "Albufeira do Azibo", "Albufeira da Baga", "Albufeira do Bemposta", "Albufeira do Cabril", "Albufeira do Carrapatelo", "Albufeira do Castelo de Bode", "Albufeira da Coa", "Albufeira do Douro Internacional", "Albufeira do Feiticeiro", "Albufeira da Foz Tua", "Albufeira do Fratel", "Albufeira da Grama", "Albufeira da Guadiana", "Albufeira do Lindoso", "Albufeira do Maranhão", "Albufeira do Miranda", "Albufeira do Monte da Rocha", "Albufeira do Ocreza", "Albufeira da Paradela", "Albufeira do Picote", "Albufeira do Pinhão", "Albufeira do Pocinho", "Albufeira da Ponte da Barca", "Albufeira da Salamonde", "Albufeira do Sabor", "Albufeira do São João da Pesqueira", "Albufeira do Torrão", "Albufeira do Vilarinho das Furnas", "Albufeira do Vírgenes"};

    search_box_ = new SearchBox(get_height(), get_width() / 2, 0, 0);
    search_box_->add_options(northMunicipalities, "Cities");
    search_box_->set_color(ColorPair::get(light0, dark0));
    search_box_->set_highlighted_color(ColorPair::get(dark0, light0));
    search_box_->set_box_color(ColorPair::get(bright_aqua, dark0));

    connected_box_ = new SearchBox(get_height() / 2 + !even_height, get_width() / 2 + !even_width,
                                   get_height() / 2, get_width() / 2);
    connected_box_->add_options(northReservoirs, "Connected Reservoirs");
    connected_box_->set_color(ColorPair::get(light0, dark0));
    connected_box_->set_highlighted_color(ColorPair::get(dark0, light0));
    connected_box_->set_box_color(ColorPair::get(light0, dark0));

    search_box_->set_userptr(connected_box_);
    connected_box_->set_userptr(search_box_);

    currently_selected_component_ = search_box_;
    previously_selected_component_ = search_box_;
}

void ReservoirBuffer::draw() {
    search_box_->draw();
    connected_box_->draw();
    cmdline_->draw();
}

void ReservoirBuffer::handle_input(int ch) {
    switch (ch) {
        case ':':
            select_component(cmdline_);
            cmdline_->show();
            break;
        case TAB:
            currently_selected_component_->set_box_color(ColorPair::get(light0, dark0));

            select_component((Component*) previously_selected_component_->get_userptr());

            currently_selected_component_->set_box_color(ColorPair::get(bright_aqua, dark0));
            break;
        default:
            currently_selected_component_->handle_input(ch);
            break;
    }
}