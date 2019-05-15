//
// Created by liuqian8 on 2019/4/17.
//

#pragma once

#include <Context.h>

class Application
{
public:
    Application();
    virtual ~Application();
public:
    virtual void CreateScence(Context* context,int width,int height) = 0;

    virtual void RenderOneFrame(Context* contex) = 0;

    virtual void Move() = 0;
};
