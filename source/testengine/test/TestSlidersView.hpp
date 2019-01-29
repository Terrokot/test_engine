//
//  TestSlidersView.hpp
//  TestEngine
//
//  Created by Vladas Zakrevskis on 1/29/2019.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include "LabeledSliderView.hpp"

class TestSlidersView : public ui::View {

public:

    using View::View;

    ui::LabeledSliderView* _x_view = nullptr;
    ui::LabeledSliderView* _y_view = nullptr;
    ui::LabeledSliderView* _z_view = nullptr;

private:

    void _setup() override;
};
