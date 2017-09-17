//
//  System.hpp
//  TestEngine
//
//  Created by Vladas Zakrevskis on 8/19/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#include "Types.h"
#include "Platform.h"
#include "Time.hpp"

class System {
    
public:
    
    static void sleep(Float interval);
    static UInt random();
    static UInt random(Int range);
};
