//
// Created by liuqian8 on 2019/6/4.
//
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

void View::Update()
{

}

void View::Render()
{

}