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
    void BaseCreateScence(Context* context,int width,int height);

    virtual void CreateScence(Context* context,int width,int height) = 0;

    virtual void RenderOneFrame(Context* contex) = 0;

    virtual void Move() = 0;

    bool isInitial()const { return isInitial_;}

protected:
    bool isInitial_;
};
