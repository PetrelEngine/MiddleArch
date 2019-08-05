//
// Created by liuqian8 on 2019/6/4.
//
#include "View.h"
#include "Graphics.h"
#include "Camera.h"
View::View(Context *context):
    Object(context),
    graphics_(getSubsystem<Graphics>()),
    cullCamera_(nullptr)
{
    frame_.camera_ = nullptr;
}

View::~View()
{

}
Graphics* View::getGraphics() const
{
    return graphics_;
}

void View::setCameraShaderParameters(Camera* camera)
{
    graphics_->setShaderParameter(VSP_VIEWPROJ,camera->getCamera());
    graphics_->setShaderParameter(VSP_VIEW,camera->getFrustum());
}

void View::update(const FrameInfo& frame)
{
    frame_.camera_ = cullCamera_;
    frame_.timeStep_ = frame.timeStep_;
    frame_.frameNumber_ = frame.frameNumber_;
    frame_.viewSize_ = viewSize_;
}

void View::render()
{

}