//
// Created by liuqian8 on 2019/6/4.
//
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "View.h"
#include "Graphics.h"
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

void View::setCameraShaderParameters()
{
    graphics_->setShaderParameter(VSP_VIEWPROJ,glm::perspective(glm::radians(120.0f), (float)1080 / (float)1920, 0.1f, 100.0f));
    graphics_->setShaderParameter(VSP_VIEW,glm::lookAt(glm::vec3(0,1,1),glm::vec3(0,0,0),glm::vec3(0,1,0)));
}

void View::Update()
{

}

void View::Render()
{

}