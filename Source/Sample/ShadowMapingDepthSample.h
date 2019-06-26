//
// Created by liuqian8 on 2019/6/26.
//
#pragma once
#include "Application.h"
#include "ShadowMapingDepth.h"
class ShadowMapingDepthSample: public Application
{
public:
    ShadowMapingDepthSample();

    ~ShadowMapingDepthSample();

    virtual void Move();

    virtual void CreateScence(Context* context,int width,int height);

    virtual void RenderOneFrame(Context* context);

protected:
    ShadowMapingDepth* shadowMapingDepth_;
};
