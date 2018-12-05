//
//  Drawable.hpp
//  TestEngine
//
//  Created by Vladas Zakrevskis on 10/03/2018.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include "Color.hpp"
#include "NonCopyable.hpp"

class Drawable : public NonCopyable {
    
protected:
    
    virtual void draw() = 0;

public:

    float rotation = 0;
	ui::Color _color;
};
