//
// Created by liuqian8 on 2019/2/21.
//

#pragma once

#include "RenderingCompositionGraph.h"
#include "PassPostProcessAA.h"

class TestDAG
{
public:
    TestDAG();
    virtual ~TestDAG();

    void DAGTest()
    {
        RenderingCompositeOutputRef PostProcessDownsample;
        PassPostProcessAA* nodes = new PassPostProcessAA();
        renderProcessContext_ = new RenderingCompositePassContext();

        PassDag_->RegisterPass(nodes);

        PostProcessDownsample = RenderingCompositeOutputRef(nodes);
        nodes->SetInput(ePId_Input0,PostProcessDownsample);
//        renderProcessContext_ = new RenderingCompositePassContext();

        renderProcessContext_->Process(nodes);


    }

    int Sum_Solution(int n)
    {
        int result = 0;
        int temp = 0;
        bool flag = (n>0) && temp == (result = Sum_Solution(n - 1));
        result += n;
        return result;
    }

private:
    RenderingCompositionGraph*  PassDag_;
    RenderingCompositePassContext* renderProcessContext_;
};
