//
// Created by liuqian8 on 2019/6/28.
//
#pragma once
#include "Application.h"
#include "FresnelReflection.h"
class FresnelReflectionSample: public Application
{
public:
    FresnelReflectionSample();

    ~FresnelReflectionSample();

    virtual void CreateScence(Context* context,int width,int height);

    virtual void RenderOneFrame(Context* context);

    virtual void Move();

private:
    FresnelReflection* fresnelReflection_;
};
