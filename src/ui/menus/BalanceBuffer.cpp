#include "BalanceBuffer.h"
#include "colors/ColorPair.h"
#include "BasicMetricsBuffer.h"
#include "components/KeysBindings.h"
#include "pallets/gruvbox.h"
#include "GraphClasses/StaticGraph.h"

BalanceBuffer::BalanceBuffer() : Buffer() {
    old_average_ = new TextLabel(20, 7, get_width() / 4 - 4);
    old_average_->set_color(ColorPair::get(light0, dark0));

    old_variance_ = new TextLabel(20, 9, get_width() / 4 - 3);
    old_variance_->set_color(ColorPair::get(light0, dark0));

    old_max_diff_ = new TextLabel(10, 11, get_width() / 4 + 7);
    old_max_diff_->set_color(ColorPair::get(light0, dark0));


    new_average_ = new TextLabel(10, 7, get_width() * (3.0 / 4));
    new_average_->set_color(ColorPair::get(light0, dark0));

    new_variance_ = new TextLabel(10, 9, get_width() * (3.0 / 4) + 1);
    new_variance_->set_color(ColorPair::get(light0, dark0));

    new_max_diff_ = new TextLabel(10, 11, get_width() * (3.0 / 4) + 11);
    new_max_diff_->set_color(ColorPair::get(light0, dark0));


    meets_demands_ = new TextLabel(10, 15, get_width() / 2 + 6);
    meets_demands_->set_color(ColorPair::get(bright_red, dark0));

    this->hide();
    wbkgd(get_win(), COLOR_PAIR(ColorPair::get(light0, dark0)));
    this->set_color(ColorPair::get(light0, dark0));
    this->on_select([&] {
       // TODO: balance

       if (meets_demand()) {
           meets_demands_->set_text("true");
           meets_demands_->set_color(ColorPair::get(bright_green, dark0));
       }
       else {
           meets_demands_->set_text("false");
           meets_demands_->set_color(ColorPair::get(bright_red, dark0));
       }
    });
}

void BalanceBuffer::draw() {
    mvwprintw(get_win(), 4, get_width() / 2 - 1, "%s", "vs.");
    mvwprintw(get_win(), 4, get_width() / 4 - 5, "%s", "Old");
    mvwprintw(get_win(), 4, get_width() * (3.0 / 4) + 1, "%s", "New");
    mvwprintw(get_win(), 2, get_width() / 2 - 3, "%s", "Balance");

    for (int y = 7; y < 13; y++) {
        mvwprintw(get_win(), y, get_width() / 2, "%s", "│");
    }

    // old
    mvwprintw(get_win(), 7, get_width() / 4 - 13, "%s", "Average:");
    mvwprintw(get_win(), 9, get_width() / 4 - 13, "%s", "Variance:");
    mvwprintw(get_win(), 11, get_width() / 4 - 13, "%s", "Maximum Difference:");

    old_average_->draw();
    old_variance_->draw();
    old_max_diff_->draw();

    // new
    mvwprintw(get_win(), 7, get_width() * (3.0 / 4) - 9, "%s", "Average:");
    mvwprintw(get_win(), 9, get_width() * (3.0 / 4) - 9, "%s", "Variance:");
    mvwprintw(get_win(), 11, get_width() * (3.0 / 4) - 9, "%s", "Maximum Difference:");

    new_average_->draw();
    new_variance_->draw();
    new_max_diff_->draw();

    // meets demand
    mvwprintw(get_win(), 15, get_width() / 2 - 8, "%s", "Meets demand:");

    meets_demands_->draw();
}

void BalanceBuffer::handle_input(int ch) {
    switch (ch) {
        case ESC:
            if (previous_buffer_ != nullptr) {
                next_buffer_ = previous_buffer_;
            }
    }

}

bool BalanceBuffer::meets_demand() {
    for (const auto& pair : City::getCitiesMap()) {
        City* city = pair.second;

        if (city->getDemand() - city->getFlow() != 0) {
            return false;
        }
    }

    return true;
}

void BalanceBuffer::show() const {
    show_panel(get_panel());

    old_average_->show();
    old_variance_->show();
    old_max_diff_->show();

    new_average_->show();
    new_variance_->show();
    new_max_diff_->show();

    meets_demands_->show();
}

void BalanceBuffer::hide() const {
    old_average_->hide();
    old_variance_->hide();
    old_max_diff_->hide();

    new_average_->hide();
    new_variance_->hide();
    new_max_diff_->hide();

    meets_demands_->hide();
    hide_panel(get_panel());
}

BalanceBuffer::~BalanceBuffer() {
    delete old_average_;
    delete old_variance_;
    delete old_max_diff_;

    delete new_average_;
    delete new_variance_;
    delete new_max_diff_;

    delete meets_demands_;
}