//
// Created by liuqian8 on 2019/5/6.
//

#pragma once

#include "Deferred.h"
#include "Application.h"

class DeferredRenderSample: public Application
{
public:
    DeferredRenderSample();

    ~DeferredRenderSample();

    virtual void CreateScence(Context* context,int width,int height);

    virtual void RenderOneFrame(Context* context);

    virtual void Move();

private:
    Context*                    Context_;
    Deferred*                   Deferred_;
};
