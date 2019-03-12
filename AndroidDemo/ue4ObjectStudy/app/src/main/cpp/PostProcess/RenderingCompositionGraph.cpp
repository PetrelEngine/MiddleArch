//
// Created by liuqian8 on 2019/2/13.
//
#include "RenderingCompositionGraph.h"


RenderingCompositionGraph::RenderingCompositionGraph()
{

}

RenderingCompositionGraph::~RenderingCompositionGraph()
{

}

void RenderingCompositionGraph::RecursivelyGatherDependencies(RenderingCompositePass *Pass)
{
    if(Pass->bComputeOutputDescWasCalled)
    {
        //alread processed
        return;
    }

    Pass->bComputeOutputDescWasCalled = true;
    LOGE("RecursivelyGatherDependencies start iterate.");
    //iterate through all inputs and additional dependencies of this pass
    unsigned Index = 0;
    while(const RenderingCompositeOutputRef* OutputRefIt = Pass->GetDependency(Index++))
    {
        LOGE("RecursivelyGatherDependencies contains iterate.");
        RenderingCompositeOutput* InputOutput = OutputRefIt->GetOutput();
        LOGE("InputOutput is NULL.: %p",InputOutput);
        if(InputOutput)
        {
            LOGE("RecursivelyGatherDependencies add dependency.");
            //add a dependency to this output as we are referencing to it
            InputOutput->AddDependency();
        }

        if(RenderingCompositePass* OutputRefItPass = OutputRefIt->GetPass())
        {
            // recursively process all inputs of this Pass
            RecursivelyGatherDependencies(OutputRefItPass);
        }
    }
}

RenderingCompositePassContext::RenderingCompositePassContext():
        bWasProcessed(false)
{

}

RenderingCompositePassContext::~RenderingCompositePassContext()
{

}

void RenderingCompositePassContext::Process(const vector<RenderingCompositePass *> &TargetRoots)
{
    bWasProcessed = true;
    if(TargetRoots.size() == 0)
    {
        return;
    }
    LOGE("Process..");
    for(RenderingCompositePass* Root:TargetRoots)
    {
        LOGE("Process for iterate.");
        Graph.RecursivelyGatherDependencies(Root);
    }
}


RenderingCompositePass* RenderingCompositeOutputRef::GetPass() const
{
    return Source;
}

RenderingCompositeOutput* RenderingCompositeOutputRef::GetOutput() const
{
    if(Source == 0)
    {
        return NULL;
    }

    return Source->GetOutput(PassOutputId);
}