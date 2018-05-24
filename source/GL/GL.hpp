//
//  GL.hpp
//  TestEngine
//
//  Created by Vladas Zakrevskis on 8/17/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#define GLM_FORCE_RADIANS

#include "glm\glm.hpp"

#if APPLE
    #include <glm/gtc/matrix_transform.hpp>
#else
    #include "glm\gtc\matrix_transform.hpp"
#endif

using namespace glm;

#ifdef WINDOWS
    #include <glew.h>
    #include "GLFW\glfw3.h"

#elif IOS
    #import <OpenGLES/ES3/gl.h>

#elif MAC_OS
    #include "glew.h"
    #include "glfw3.h"
#endif

#include "Shader.hpp"

