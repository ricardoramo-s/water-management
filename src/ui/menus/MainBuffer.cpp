#include "MainBuffer.h"
#include "pallets/gruvbox.h"
#include "components/KeysBindings.h"

MainBuffer::MainBuffer() : Buffer() {
    basic_metrics_ = new TextLabel(25, get_height() * (1.0 / 3), get_width() / 2 - 12);
    basic_metrics_->set_text("> Basic Service Metrics <");
    basic_metrics_->set_color(ColorPair::get(light0, dark0));
    basic_metrics_->on_highlight([&] {
        basic_metrics_->set_color(ColorPair::get(dark0, light0));
        failure_->set_color(ColorPair::get(light0, dark0));
    });
    basic_metrics_->on_select([&] {
        if (!metrics_buffer_) {
            metrics_buffer_ = new BasicMetricsBuffer();
            metrics_buffer_->previous_buffer(this);
        }

        next_buffer_ = metrics_buffer_;
    });

    failure_ = new TextLabel(43, get_height() * (2.0 / 3), get_width() / 2 - 21);
    failure_->set_text("> Reliability and Sensitivity to Failures <");
    failure_->set_color(ColorPair::get(light0, dark0));
    failure_->on_highlight([&] {
        basic_metrics_->set_color(ColorPair::get(light0, dark0));
        failure_->set_color(ColorPair::get(dark0, light0));
    });
    failure_->on_select([&] {
       if (!failure_buffer_) {
           failure_buffer_ = new FailureBuffer();
           failure_buffer_->previous_buffer(this);
       }

       next_buffer_ = failure_buffer_;
    });

    basic_metrics_->set_next_component(failure_);
    failure_->set_next_component(basic_metrics_);

    select_component(basic_metrics_);
    basic_metrics_->highlight();

    wbkgd(get_win(), COLOR_PAIR(ColorPair::get(light0, dark0)));
    this->set_color(ColorPair::get(light0, dark0));
    this->hide();
    this->on_select([&] {

    });
}

void MainBuffer::handle_input(int ch) {
    switch (ch) {
        case ESC:
            quit();
            break;
        case TAB:
            select_component(currently_selected_component_->get_next_component());
            currently_selected_component_->highlight();
            break;
        default:
            currently_selected_component_->handle_input(ch);
    }
}

void MainBuffer::draw() {
    basic_metrics_->draw();
    failure_->draw();
}

void MainBuffer::hide() const {

}

void MainBuffer::show() const {

}

MainBuffer::~MainBuffer() {
    delete basic_metrics_;
    delete failure_;
    delete metrics_buffer_;
}
