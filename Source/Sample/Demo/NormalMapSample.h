//
// Created by liuqian8 on 2019/5/22.
//
#pragma once

#include "NormalMap.h"
#include "Application.h"

class NormalMapSample: public Application
{
public:
    NormalMapSample();

    ~NormalMapSample();

    virtual void CreateScence(Context* context,int width,int height);

    virtual void RenderOneFrame(Context* context);

    virtual void Move();

protected:
    NormalMap*          normalMap_;
};
