//
//  Events.hpp
//  TestEngine
//
//  Created by Vladas Zakrevskis on 11/03/2018.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include "Point.hpp"
#include "Event.hpp"

class View;
class World;

class Events {
public:
    static Event<World, Point> onRotation;
    static Event<World, Point> onMove;
};
