//
// Created by liuqian8 on 2019/5/15.
//
#pragma once

#include "ParallaxMapping.h"
#include "Context.h"
#include "Application.h"

class ParallaxMappingSample: public Application
{
public:
    ParallaxMappingSample();
    ~ParallaxMappingSample();

    virtual void CreateScence(Context* context,int width,int height);

    virtual void RenderOneFrame(Context* context);

    virtual void Move();

private:
    Context*                    Context_;
    ParallaxMapping*            ParallaxMapping_;
};
