#include "ReservoirMenu.h"

ReservoirMenu::ReservoirMenu() {
    std::vector<std::string> northMunicipalities = {"Alijó","Amares","Arcos de Valdevez","Barcelos","Boticas","Braga","Bragança","Cabeceiras de Basto","Caminha","Celorico de Basto","Chaves","Espinho","Esposende","Fafe","Felgueiras","Guimarães","Lamego","Lousada","Maia","Marco de Canaveses","Matosinhos","Melgaço","Mesão Frio","Mirandela","Mogadouro","Monção","Montalegre","Murça","Oliveira de Azeméis","Paços de Ferreira","Paredes","Paredes de Coura","Penafiel","Peso da Régua","Ponte da Barca","Ponte de Lima","Póvoa de Lanhoso","Póvoa de Varzim","Ribeira de Pena","Sabrosa","Santa Maria da Feira","Santo Tirso","São João da Madeira","Terras de Bouro","Trofa","Valença","Valongo","Valpaços","Viana do Castelo","Vieira do Minho","Vila do Conde","Vila Flor","Vila Nova de Cerveira","Vila Nova de Famalicão","Vila Nova de Foz Côa","Vila Nova de Gaia","Vila Nova de Paiva","Vila Pouca de Aguiar","Vila Real","Vimioso"};
    std::vector<std::string> northReservoirs = {"Alto Rabagão", "Albufeira da Aguieira", "Albufeira do Azibo", "Albufeira da Baga", "Albufeira do Bemposta", "Albufeira do Cabril", "Albufeira do Carrapatelo", "Albufeira do Castelo de Bode", "Albufeira da Coa", "Albufeira do Douro Internacional", "Albufeira do Feiticeiro", "Albufeira da Foz Tua", "Albufeira do Fratel", "Albufeira da Grama", "Albufeira da Guadiana", "Albufeira do Lindoso", "Albufeira do Maranhão", "Albufeira do Miranda", "Albufeira do Monte da Rocha", "Albufeira do Ocreza", "Albufeira da Paradela", "Albufeira do Picote", "Albufeira do Pinhão", "Albufeira do Pocinho", "Albufeira da Ponte da Barca", "Albufeira da Salamonde", "Albufeira do Sabor", "Albufeira do São João da Pesqueira", "Albufeira do Torrão", "Albufeira do Vilarinho das Furnas", "Albufeira do Vírgenes"};

    multiTextBox = new MultiComponent<TextBox>();
    auto text_box1 = new TextBox(height_ / 2 - 1, (width_ / 2) - 3, height_ - height_ / 2, width_ / 2 + 2, false);
    auto text_box2 = new TextBox(height_ / 2 - 1, (width_ / 2) - 3, height_ - height_ / 2, width_ / 2 + 2, false);

    text_box1->set_lines_(northMunicipalities);
    text_box1->set_header_("Connected Cities");
    text_box2->set_lines_(northReservoirs);
    text_box2->set_header_("Connected Reservoirs");

    multiTextBox->add_component(text_box1);
    multiTextBox->add_component(text_box2);
}

void ReservoirMenu::draw() {
    multiTextBox->draw();
}

void ReservoirMenu::handle_input(int ch) {
    multiTextBox->handle_input(ch);
}