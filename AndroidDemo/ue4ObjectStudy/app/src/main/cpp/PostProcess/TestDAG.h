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

private:
    RenderingCompositionGraph*  PassDag_;
    RenderingCompositePassContext* renderProcessContext_;
};
