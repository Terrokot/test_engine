//
//  TestView.hpp
//  TestEngine
//
//  Created by Vladas Zakrevskis on 4/29/2019.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include "Button.hpp"
#include "ImageView.hpp"
#include "DrawingView.hpp"
#include "AnalogStickView.hpp"
#include "Vec4SlidersView.hpp"

class TestView : public ui::View {

public:
    
    static inline Event<gm::Point> on_left_stick_move;
    static inline Event<gm::Point> on_right_stick_move;

    using ui::View::View;

    ui::View* revolving_view;

    ui::Button* button;
    ui::ImageView* image;
    ui::AnalogStickView* left_stick;
    ui::AnalogStickView* right_stick;

    static inline Vec4SlidersView* sliders = nullptr;

    void _setup() override;
    void _layout() override;

};
