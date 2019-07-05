//
// Created by liuqian8 on 2019/2/21.
//
#pragma once
#include "Application.h"
#include "RenderingCompositionGraph.h"
#include "PassPostProcessAA.h"

class TestDAG: public Application
{
public:
    TestDAG();
    virtual ~TestDAG();

    virtual void Move();

    virtual void CreateScence(Context* context,int width,int height);

    virtual void RenderOneFrame(Context* context);


private:
    RenderingCompositionGraph*  PassDag_;
    RenderingCompositePassContext* renderProcessContext_;
};
