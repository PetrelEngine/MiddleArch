//
// Created by liuqian8 on 2019/5/20.
//
#pragma once

#include "GammaCorrection.h"
#include "Context.h"
#include "Application.h"

class GammaCorrectionSample:public Application
{
public:
    GammaCorrectionSample();
    ~GammaCorrectionSample();

    virtual void CreateScence(Context* context,int width,int height);

    virtual void RenderOneFrame(Context* context);

    virtual void Move();


private:
    Context*                    Context_;
    GammaCorrection*            GammaCorrection_;
};
