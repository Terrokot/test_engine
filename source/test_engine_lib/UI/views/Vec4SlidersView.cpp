//
//  Vec4SlidersView.cpp
//  TestEngine
//
//  Created by Vladas Zakrevskis on 2/18/2019.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include "Log.hpp"

#include "Vec4SlidersView.hpp"

#define SET_VALUE(var, val) var = (-1 + val * 2 * multiplier);

Vec4SlidersView::~Vec4SlidersView() {
    delete  _x_slider;
    delete  _y_slider;
    delete  _z_slider;
    delete  _w_slider;
}

void Vec4SlidersView::_setup() {
    _x_slider = new ui::LabeledSliderView();
    _y_slider = new ui::LabeledSliderView();
    _z_slider = new ui::LabeledSliderView();
    _w_slider = new ui::LabeledSliderView();

    add_subview({ _x_slider,
                  _y_slider,
                  _z_slider,
                  _w_slider });

    _x_slider->set_caption("X");
    _y_slider->set_caption("Y");
    _z_slider->set_caption("Z");
    _w_slider->set_caption("W");

    _x_slider->set_slider_color(gm::Color::red);
    _y_slider->set_slider_color(gm::Color::green);
    _z_slider->set_slider_color(gm::Color::blue);
    _w_slider->set_slider_color(gm::Color::turquoise);

    _w_slider->slider_view->multiplier = 2.0f;

    _x_slider->slider_view->on_value_changed.subscribe([&](float value) {
        SET_VALUE(position.x, value);
        on_change(position);
    });

    _y_slider->slider_view->on_value_changed.subscribe([&](float value) {
        SET_VALUE(position.y, value);
        on_change(position);
    });

    _z_slider->slider_view->on_value_changed.subscribe([&](float value) {
        SET_VALUE(position.z, value);
        on_change(position);
    });

    _w_slider->slider_view->on_value_changed.subscribe([&](float value) {
        SET_VALUE(position.w, value);
        on_change(position);
    });
}

void Vec4SlidersView::_layout() {
    _calculate_absolute_frame();

    static const float margin = 4;
    const float width = (_frame.size.width - margin * 2) / 4;

    _x_slider->set_frame({ width * 0 + margin * 0, 0, width, _frame.size.height });
    _y_slider->set_frame({ width * 1 + margin * 1, 0, width, _frame.size.height });
    _z_slider->set_frame({ width * 2 + margin * 1, 0, width, _frame.size.height });
    _w_slider->set_frame({ width * 3 + margin * 1, 0, width, _frame.size.height });

    _layout_subviews();
}
