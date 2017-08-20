//
//  Window.cpp
//  TestEngine
//
//  Created by Vladas Zakrevskis on 8/20/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#include "UI/Window.hpp"
#include "GL/GL.hpp"
#include "Tools/Log.hpp"

void windowSizeChanged(GLFWwindow* window, int width, int height);

Size Window::size;
GLFWwindow * Window::window;

void Window::initialize(int width, int height) {
    
    size = Size(width, height);
    
    glfwInit();
    
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL
    
    window = glfwCreateWindow(width, height, "Test Engine", NULL, NULL);
    
    if (window == nullptr) { Error("GLFW window creation failed"); return; }
    
    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, windowSizeChanged);
    
    glewExperimental = true;
    if (glewInit()) { Error("Glew initialization failed"); }
}

void windowSizeChanged(GLFWwindow* window, int width, int height) {
    
    Window::size.width  = width;
    Window::size.height = height;
}
