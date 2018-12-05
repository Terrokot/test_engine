//
//  GL.hpp
//  TestEngine
//
//  Created by Vladas Zakrevskis on 8/17/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#include "Rect.hpp"
#include "Color.hpp"

#include "Matrix4.hpp"

#if IOS
    #import <OpenGLES/ES3/gl.h>
#else
    #include <GL/glew.h>
    #include <GLFW/glfw3.h>
#endif

#include "Shader.hpp"

class GL {
public:
	static void set_viewport(const ui::Rect& rect) {
		glViewport((GLint)rect.origin.x, (GLint)rect.origin.y, (GLsizei)rect.size.width, (GLsizei)rect.size.height);
	}
    
    static void unbind_image() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    static void set_clear_color(const ui::Color& color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }
};
