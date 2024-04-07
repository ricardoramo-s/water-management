#ifndef WATER_MANAGEMENT_BALANCEBUFFER_H
#define WATER_MANAGEMENT_BALANCEBUFFER_H

#include "components/TextLabel.h"
#include "menus/Buffer.h"


class BalanceBuffer : public Buffer {
private:
    TextLabel *old_average_, *old_variance_, *old_max_diff_;
    TextLabel *new_average_, *new_variance_, *new_max_diff_;

    TextLabel *meets_demands_;

    bool meets_demand();

public:
    BalanceBuffer();

    void draw() override;
    void handle_input(int ch) override;

    void hide() const override;
    void show() const override;

    ~BalanceBuffer() override;
};


#endif //WATER_MANAGEMENT_BALANCEBUFFER_H
