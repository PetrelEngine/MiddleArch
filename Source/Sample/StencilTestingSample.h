//
// Created by liuqian8 on 2019/5/20.
//

#pragma once

#include "StencilTesting.h"
#include "Application.h"

class StencilTestingSample: public Application
{
public:
    StencilTestingSample();

    ~StencilTestingSample();

    virtual void Move();

    virtual void CreateScence(Context* context,int width,int height);

    virtual void RenderOneFrame(Context* context);

protected:
    StencilTesting* StencilTesting_;
};
