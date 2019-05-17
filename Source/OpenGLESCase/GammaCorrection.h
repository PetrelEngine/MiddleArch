//
// Created by liuqian8 on 2019/5/17.
//
#pragma once
#include "Context.h"



class GammaCorrection
{
public:
    GammaCorrection();
    ~GammaCorrection();

    void CreateScence(Context* context,int width,int height);

    void RenderFrame();

protected:

};
