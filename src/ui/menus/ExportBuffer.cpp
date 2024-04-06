#include "ExportBuffer.h"
#include "colors/ColorPair.h"
#include "pallets/gruvbox.h"

ExportBuffer::ExportBuffer() : Buffer() {
    input_box_ = new InputBox(get_width() / 2, get_height() / 2 - 1, get_width() / 4, "❯ ");
    input_box_->set_header_("Export to file:");
    input_box_->set_color(ColorPair::get(light0, dark0));
    input_box_->set_box_color(ColorPair::get(light0, dark0));
    input_box_->on_select([&] {
        // TODO: exporting
    });
    input_box_->on_cancel([&] {
        next_buffer_ = previous_buffer_;
    });

    set_color(ColorPair::get(light0, dark0));
    this->hide();
    this->on_select([&] {
        input_box_->clear();
    });
}

void ExportBuffer::handle_input(int ch) {
    input_box_->handle_input(ch);
}

void ExportBuffer::draw() {
    input_box_->draw();
}

void ExportBuffer::hide() const {
    hide_panel(get_panel());
    input_box_->hide();
}

void ExportBuffer::show() const {
    show_panel(get_panel());
    input_box_->show();
}

ExportBuffer::~ExportBuffer() {
    delete input_box_;

    delwin(get_win());
    del_panel(get_panel());
}
