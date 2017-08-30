//
//  Input.hpp
//  TestEngine
//
//  Created by Vladas Zakrevskis on 8/30/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

class Input {
    
public:
    
    static void touchBegan(double x, double y);
    static void touchMoved(double x, double y);
    static void touchEnded(double x, double y);
};
