//
// Created by liuqian8 on 2019/6/4.
//
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "View.h"
#include "Graphics.h"
#include "Camera.h"
View::View(Context *context):
    Object(context),
    graphics_(getSubsystem<Graphics>())
{

}

View::~View()
{

}
Graphics* View::GetGraphics() const
{
    return graphics_;
}

void View::setCameraShaderParameters(Camera* camera)
{
    graphics_->setShaderParameter(VSP_VIEWPROJ,camera->getCamera());
    graphics_->setShaderParameter(VSP_VIEW,camera->getFrustum());
}

void View::Update()
{

}

void View::Render()
{

}