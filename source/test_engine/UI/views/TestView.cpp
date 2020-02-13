//
//  TestView.cpp
//  TestEngine
//
//  Created by Vladas Zakrevskis on 4/29/2019.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include "Log.hpp"
#include "Time.hpp"
#include "System.hpp"
#include "Assets.hpp"
#include "Dispatch.hpp"
#include "TestView.hpp"
#include "RootView.hpp"

using namespace cu;
using namespace ui;
using namespace gm;

void TestView::_setup() {

    add_subview(object_info_view = new ObjectInfoView());

    object_info_view->edit_frame() =
            { 300,
              300,
              300,
              300
            };

    object_info_view->enable_resize();

    button = new Button();
    button->set_caption("Button");
    add_subview(button);

    add_subview(revolving_view = View::dummy());


#ifndef DESKTOP_BUILD
    add_subview(left_stick = new AnalogStickView());
    left_stick->on_direction_change = [](auto point) {
        TestView::on_left_stick_move(point);
    };

    add_subview(right_stick = new AnalogStickView());
    right_stick->on_direction_change = [](auto point) {
        TestView::on_right_stick_move(point);
    };
#endif

    image = new ImageView({ 60, 80 }, Assets::images->cat);
    add_subview(image);

    sliders = new Vec4SlidersView();
    sliders->edit_frame() = { 0, 100, 200, 300 };
    add_subview(sliders);

    switcher = new Switch();
    add_subview(switcher);

    switcher->on_value_changed = [](bool value) {
        te::RootView::set_draw_touches(value);
    };

    button->on_press = [&] {
        cu::System::alert("Hellou");
        button->background_color = Color::random();
    };

    enable_touch();

    on_touch = [](Touch* touch) {
        if (touch->is_began()
#ifdef DESKTOP_BUILD
            && touch->is_left_click()
#endif
        ) {
            if (SelectionScene::instance) {

                auto ray = SelectionScene::instance->camera->cast_ray(touch->location);

                auto axis = SelectionScene::instance->select_axis(ray);

                Log((int)axis);

                auto model = SelectionScene::instance->select_model(ray);

                if (model != nullptr) {
                    object_info_view->set_object(model);
                }
                else {
                    object_info_view->clear();
                }
            }
        }
    };

}

void TestView::_layout() {

    _frame = _superview->frame().with_zero_origin();

    button->edit_frame() =
            { 0,
              _frame.size.height - 100,
              100,
              100
            };

    static const float margin = 40;


#ifndef DESKTOP_BUILD
    left_stick->set_center({
        left_stick->frame().size.width / 2 + margin,
        _frame.size.height - left_stick->frame().size.height / 2 - margin,
    });

    right_stick->set_center({
        _frame.size.width - right_stick->frame().size.width / 2 - margin,
        _frame.size.height - right_stick->frame().size.height / 2 - margin,
    });
#endif

    static float angle = 0;
    revolving_view->set_center(Point::on_circle(200, angle, { 300, 300 }));
    angle += 0.01;

    auto switcher_size = 100.0f;

    switcher->edit_frame() =
            { _frame.size.width - switcher_size - 20,
              20,
              switcher_size,
              switcher_size / 2
            };

    image->set_center({ _frame.size.width / 2, _frame.size.height - 100 });

    View::_layout();
}
