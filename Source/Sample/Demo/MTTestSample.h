//
// Created by liuqian8 on 2019/6/3.
//
#pragma once
#include "Application.h"
#include "TestWorkerThread.h"

class MTTestSample: public Application
{
public:
    MTTestSample();

    ~MTTestSample();

    virtual void CreateScence(Context* context,int width,int height);

    virtual void RenderOneFrame(Context* context);

    virtual void Move();
private:
    TestWorkerThread* producer;
    TestWorkerThread* consumer;
    Mutex*        mutex_;
};
