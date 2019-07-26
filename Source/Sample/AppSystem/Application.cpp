//
// Created by liuqian8 on 2019/4/17.
//
#include "Application.h"

Application::Application():
        isInitial_(false)
{

}

Application::~Application()
{

}

void Application::BaseCreateScence(Context *context, int width, int height)
{
    CreateScence(context,width,height);
    isInitial_ = true;
}