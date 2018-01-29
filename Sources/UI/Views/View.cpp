//
//  View.cpp
//  TestEngine
//
//  Created by Vladas Zakrevskis on 8/28/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#include "View.hpp"
#include "Buffer.hpp"
#include "Shader.hpp"
#include "Window.hpp"

View::View(float x, float y, float width, float height) : frame(Rect(x, y, width, height)) { }
View::View(float width, float height) : View(0, 0, width, height) { }
View::View(const Size &size) : View(0, 0, size.width, size.height) { }
View::~View() { delete buffer; }

BufferData * View::getBufferData() {
    return absoluteFrame().getData();
}

Rect View::absoluteFrame() {
    Rect aFrame = frame;
    View *superview = this->superview;
    while (superview != nullptr) {
        aFrame.origin += superview->frame.origin;
        superview = superview->superview;
    }
    return aFrame;
}

void View::setupBuffer() {
    if (buffer != nullptr) delete buffer;
    buffer = new Buffer(getBufferData(), BufferConfiguration(2));
}

void View::drawSubviews() const {
    if (subviews.empty()) return;
    for (auto subview : subviews) subview->draw();
}

void View::draw() {
    Shader::ui.use();
    Shader::ui.setUniformColor(color);
    buffer->draw();
    drawSubviews();
}

void View::layout() {
        
    if (matolayoutMask == Matolayout::None) {
        setupBuffer();
        for (auto subview : subviews) subview->layout();
        return;
    }
    
    Rect parentFrame;
    Rect layoutFrame = frame;
    
    if (superview == nullptr) parentFrame = Rect(Window::size.width, Window::size.height);
    else parentFrame = superview->frame;
    
    if (matolayoutMask & Matolayout::StickToLeft)
        layoutFrame.origin.x = 0;
    
    if (matolayoutMask & Matolayout::StickToRight)
        layoutFrame.origin.x = parentFrame.size.width - frame.size.width;
    
    if (matolayoutMask & Matolayout::StickToTop)
        layoutFrame.origin.y = 0;
    
    if (matolayoutMask & Matolayout::StickToBottom)
        layoutFrame.origin.y = parentFrame.size.height - frame.size.height;

    if (matolayoutMask & Matolayout::Center) {
        layoutFrame.origin.x = parentFrame.size.width / 2 - frame.size.width / 2;
        layoutFrame.origin.y = parentFrame.size.height / 2 - frame.size.height / 2;
    }
    
    if (matolayoutMask & Matolayout::CenterHorizontally)
        layoutFrame.origin.x = parentFrame.size.width / 2 - frame.size.width / 2;

    if (matolayoutMask & Matolayout::CenterVertically)
        layoutFrame.origin.y = parentFrame.size.height / 2 - frame.size.height / 2;

    this->frame = layoutFrame;
    
    setupBuffer();
    
    for (auto subview : subviews) subview->layout();
}

void View::setFrame(const Rect &frame) {
    this->frame = frame;
    layout();
}

void View::setCenter(const Point &center) {
    setFrame(Rect(center.x - frame.size.width / 2,
                  center.y - frame.size.height / 2,
                  frame.size.width,
                  frame.size.height));
}

void View::addSubview(View *view) {
    subviews.push_back(view);
    view->superview = this;
}

void View::removeAllSubviews() {
    for(auto view : subviews) {
        view->removeAllSubviews();
        delete view;
    }
    subviews.clear();
}

#if MEMORY_BENCHMARK
void View::addTestViews() {
    
    if (subviews.empty()) {
        
        Size size = frame.size / 2.05;
        Color color = Color::random();
        
        auto view1 = new View(size);
        auto view2 = new View(size);
        auto view3 = new View(size);
        auto view4 = new View(size);
        
        view1->matolayoutMask = StickToTop | StickToLeft;
        view2->matolayoutMask = StickToTop | StickToRight;
        view3->matolayoutMask = StickToBottom | StickToLeft;
        view4->matolayoutMask = StickToBottom | StickToRight;
        
        view1->color = color;
        view2->color = color;
        view3->color = color;
        view4->color = color;
        
        addSubview(view1);
        addSubview(view2);
        addSubview(view3);
        addSubview(view4);
        return;
    }
    
    for(auto view : subviews) {
        view->addTestViews();
    }
}
#endif
