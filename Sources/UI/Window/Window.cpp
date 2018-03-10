//
//  Window.cpp
//  TestEngine
//
//  Created by Vladas Zakrevskis on 8/20/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#include "Window.hpp"
#include "UI.hpp"
#include "GL.hpp"
#include "RootView.hpp"

void sizeChanged(GLFWwindow* window, int width, int height);

#if GLFW
GLFWwindow * Window::window;
#endif

#if DEBUG_VIEW
DebugInfoView * Window::debugInfoView;
#endif

Size Window::size;
RootView * Window::rootView;
int Window::FPS = 0;
int Window::framesDrawn = 0;

void Window::initialize(int width, int height) {
    
    size = Size(width, height);
    
#if GLFW
    
    glfwInit();
    
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL
    
#if MAC_OS
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
#endif
    
    window = glfwCreateWindow(width, height, "Test Engine", NULL, NULL);
    
    if (window == nullptr) {
        Error("GLFW window creation failed");
        return;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, sizeChanged);
    
    glewExperimental = GL_TRUE;
    if (glewInit()) {
        Error("Glew initialization failed");
    }
    
#endif
    
    //GL(glEnable(GL_DEPTH_TEST));
    GL(glEnable(GL_BLEND));
    //GL(glEnable(GL_ALPHA_TEST));
    GL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    
    Input::initialize();
    Shader::initialize();
    Image::initialize();
    Font::initialize();
    
    GL(glClearColor(0.5, 0.5, 0.5, 1));
    
    float lineWidth[2];
    GL(glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, lineWidth));
    Log("Min line width: " << lineWidth[0]);
    Log("Max line width: " << lineWidth[1]);
    
    if (lineWidth[1] == 1) {
        Warning("glLineWidth not supported");
    }

    setup();
}

void Window::setup() {
    rootView = new RootView(Window::size.width, Window::size.height);
    
#if DEBUG_VIEW
    MEMORY_MANAGER_INVISIBLE(
        debugInfoView = new DebugInfoView();
        debugInfoView->layout();
    );
#endif
    
    rootView->setup();
    rootView->layout();
}

void Window::onDebugTick() {
    
#if MEMORY_BENCHMARK
    static int counter = 0;
    if (counter % 6 == 0) rootView->removeAllSubviews();
    rootView->addTestViews();
    rootView->layout();
    counter++;
#endif
    
#if DEBUG_VIEW
    MEMORY_MANAGER_INVISIBLE(
        debugInfoView->update();
    );
#endif

}

void Window::update() {
    GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    rootView->draw();
    
#if DEBUG_VIEW
    MEMORY_MANAGER_INVISIBLE(
        debugInfoView->draw();
    );
#endif

    FPS = 1000000000 / Time::interval();
    
    Window::framesDrawn++;
    
    if (Window::framesDrawn % 1 == 0) onDebugTick();
}

void Window::sizeChanged(GLFWwindow* window, int width, int height) {
    Window::size = Size(width, height);
    Shader::setupUiTranslation();
    rootView->frame = Rect(Window::size);
    rootView->layout();
    
    
    Log(rootView->subviews[0]->frame.toString());
    Log(rootView->subviews[1]->frame.toString());
}
