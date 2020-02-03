
#ifdef DESKTOP_BUILD

#include "GMMapping.hpp"
#include "UIMapping.hpp"

#include "Screen.hpp"
#include "TestView.hpp"
#include "TestScene.hpp"
#include "PhysicsScene.hpp"
#include "SelectionScene.hpp"
#include "TestEngineTest.hpp"

using namespace ui;


int main() {

    auto screen = new te::Screen({2000, 1680});
    screen->clear_color = gm::Color::gray;
    screen->set_view(new TestView());
    screen->set_scene(new SelectionScene());
    screen->start_main_loop();

    return 0;
}

#endif
