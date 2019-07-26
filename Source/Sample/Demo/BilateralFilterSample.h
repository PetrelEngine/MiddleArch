//
// Created by liuqian8 on 2019/7/4.
//
#pragma once
#include "Context.h"
#include "BilateralFilter.h"
#include "Application.h"
class BilateralFilterSample: public Application
{
public:
    BilateralFilterSample();

    ~BilateralFilterSample();

    virtual void CreateScence(Context* context,int width,int height);

    virtual void RenderOneFrame(Context* context);

    virtual void Move();

private:
    BilateralFilter*    bilateralFilter_;
};
