//
// Created by liuqian8 on 2019/2/21.
//
#include "TestDAG.h"

TestDAG::TestDAG():
        renderProcessContext_(nullptr)
{

}

TestDAG::~TestDAG()
{
//    if(PassDag_)
//    {
//        delete PassDag_ ;
//        PassDag_ = nullptr;
//    }

    if(renderProcessContext_)
    {
        delete renderProcessContext_;
        renderProcessContext_ = nullptr;
    }
}

void TestDAG::CreateScence(Context *context, int width, int height)
{
//    PassDag_ = new RenderingCompositionGraph();

    RenderingCompositeOutputRef PostProcessDownsample;
    PassPostProcessAA* nodes = new PassPostProcessAA();
    renderProcessContext_ = new RenderingCompositePassContext();

    renderProcessContext_->Graph.RegisterPass(nodes);
//    PassDag_->RegisterPass(nodes);

    PostProcessDownsample = RenderingCompositeOutputRef(nodes);
    nodes->SetInput(ePId_Input0,PostProcessDownsample);

    renderProcessContext_->Process(nodes);
}

void TestDAG::RenderOneFrame(Context *context)
{

}

void TestDAG::Move()
{

}

