//
// Created by liuqian8 on 2019/5/29.
//
#pragma once
#include "File.h"
#include "Context.h"
#include "Application.h"
#include "Batch.h"
class HelloTriangleSample: public Application
{
public:
    HelloTriangleSample();
    ~HelloTriangleSample();

    virtual void CreateScence(Context* context,int width,int height);

    virtual void RenderOneFrame(Context* context);

    virtual void Move();

private:
    Context*                    Context_;
    File*                       File_;

    Batch                       batch_;
    View*                       view_;
};
