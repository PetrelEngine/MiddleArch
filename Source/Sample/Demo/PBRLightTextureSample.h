//
// Created by liuqian8 on 2019/5/21.
//
#pragma once

#include "PBR_LightingTexture.h"
#include "Application.h"

class PBRLightTextureSample: public Application
{
public:
    PBRLightTextureSample();

    ~PBRLightTextureSample();

    virtual void CreateScence(Context* context,int width,int height);

    virtual void RenderOneFrame(Context* context);

    virtual void Move();

protected:
    PBR_LightingTexture*        PBR_LightingTexture_;
};
