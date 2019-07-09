//
// Created by liuqian8 on 2019/5/29.
//
#pragma once

#include "Camera.h"
#include "File.h"
#include "Context.h"
#include "Application.h"
#include "Batch.h"
#include "Texture2D.h"
class EngineSample: public Application
{
public:
    EngineSample();
    ~EngineSample();

    virtual void CreateScence(Context* context,int width,int height);

    virtual void RenderOneFrame(Context* context);

    virtual void Move();

private:
    Context*                    Context_;
    File*                       File_;

    Batch                       batch_;
    View*                       view_;
    Camera*                     camera_;
    Texture2D*                  texture2D_;
};
