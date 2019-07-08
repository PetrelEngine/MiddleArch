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
    LOGI("RecursivelyGatherDependencies start iterate.");
    //iterate through all inputs and additional dependencies of this pass
    unsigned Index = 0;
    while(const RenderingCompositeOutputRef* OutputRefIt = Pass->GetDependency(Index++))
    {
        LOGI("RecursivelyGatherDependencies contains iterate.");
        RenderingCompositeOutput* InputOutput = OutputRefIt->GetOutput();
        LOGI("InputOutput is.: %p",InputOutput);
        if(InputOutput)
        {
            LOGI("RecursivelyGatherDependencies add dependency.");
            //add a dependency to this output as we are referencing to it
            InputOutput->AddDependency();
        }

        if(RenderingCompositePass* OutputRefItPass = OutputRefIt->GetPass())
        {
            LOGI("RecursivelyGatherDependencies Recursively Gather Dependencies.");
            // recursively process all inputs of this Pass
            RecursivelyGatherDependencies(OutputRefItPass);
        }
    }
}

void RenderingCompositionGraph::RecursivelyProcess(const RenderingCompositeOutputRef &InOutputRef,RenderingCompositePassContext &Context) const
{
    LOGI("RecursivelyProcess  start");
    RenderingCompositePass *Pass = InOutputRef.GetPass();
    RenderingCompositeOutput *Output = InOutputRef.GetOutput();
    if(Pass->bProcessWasCalled)
    {
        return;
    }
    LOGI("RecursivelyProcess  start iterate.");
    Pass->bProcessWasCalled = true;
    // iterate through all inputs and additional dependencies of this pass
    int Index = 0;
    while(const RenderingCompositeOutputRef* OutputRefIt = Pass->GetDependency(Index++))
    {
        if(OutputRefIt->GetPass())
        {
            if(!OutputRefIt)
            {
                // Pass doesn't have more inputs
                break;
            }
            LOGI("RecursivelyProcess  start iterate 内部.");
            RenderingCompositeOutput* Input = OutputRefIt->GetOutput();

            Context.Pass = Pass;
            RecursivelyProcess(*OutputRefIt, Context);
        }
    }

    Context.Pass = Pass;
//    Context.SetViewportInvalid();
    // then process the pass itself
    Pass->Process(Context);

    // iterate through all inputs of this pass and decrement the references for it's inputs
    // this can release some intermediate RT so they can be reused

    int InputId = 0;

    while(const RenderingCompositeOutputRef* OutputRefIt = Pass->GetDependency(InputId++))
    {
        RenderingCompositeOutput* Input = OutputRefIt->GetOutput();

        if(Input)
        {
            Input->ResolveDependencies();
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

void RenderingCompositePassContext::Process(const vector<RenderingCompositePass *> &TargetedRoots)
{
    bWasProcessed = true;
    if(TargetedRoots.size() == 0)
    {
        return;
    }
    LOGI("Process..");
    for(RenderingCompositePass* Root:TargetedRoots)
    {
        LOGI("Process for iterate.");
        Graph.RecursivelyGatherDependencies(Root);
    }
    bool bNewOrder = true;

    if(bNewOrder)
    {
        LOGI("RenderingCompositePass iterate start。");
        LOGI("Graph.Nodes Size():%d",Graph.Nodes.size());
        for(RenderingCompositePass* Node : Graph.Nodes)
        {
            LOGI("bNewOrder is true,递归处理所有的输出操作。");
            if(Node->WasComputeOutputDescCalled())
            {
                LOGI("开始收集输出依赖项。");
                Graph.RecursivelyProcess(Node, *this);
            }
        }
    } else{
        for (RenderingCompositePass* Root : TargetedRoots)
        {
            Graph.RecursivelyProcess(Root, *this);
        }
    }

}

unsigned RenderingCompositePass::ComputeInputCount()
{
    for(unsigned i = 0; ; ++i)
    {
        if(!GetInput((EPassInputId)i))
        {
            return i;
        }
    }
}

unsigned RenderingCompositePass::ComputeOutputCount()
{
    for(unsigned i = 0; ; ++i)
    {
        if(!GetOutput((EPassOutputId)i))
        {
            return i;
        }
    }
}


RenderingCompositePass* RenderingCompositeOutputRef::GetPass() const
{
    return Source;
}

RenderingCompositeOutput* RenderingCompositeOutputRef::GetOutput() const
{
    if(Source == NULL)
    {
        return NULL;
    }
    return Source->GetOutput(PassOutputId);
}