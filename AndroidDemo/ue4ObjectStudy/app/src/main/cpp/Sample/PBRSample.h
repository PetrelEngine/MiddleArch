//
// Created by liuqian8 on 2019/4/17.
//
#pragma once

#include "Application.h"

class PBRSample: public Application
{
public:
    PBRSample();
    ~PBRSample();

    virtual void CreateScence(Context* context,int width,int height);

    virtual void RenderOneFrame(Context* context);

private:
    Context* Context_;
};
