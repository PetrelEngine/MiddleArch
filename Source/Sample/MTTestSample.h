//
// Created by liuqian8 on 2019/6/3.
//
#pragma once
#include "Application.h"
#include "WorkerThread.h"

class MTTestSample: public Application
{
public:
    MTTestSample();

    ~MTTestSample();

    virtual void CreateScence(Context* context,int width,int height);

    virtual void RenderOneFrame(Context* context);

    virtual void Move();
private:
    WorkerThread* producer;
    WorkerThread* consumer;
    Mutex*        mutex_;
};
