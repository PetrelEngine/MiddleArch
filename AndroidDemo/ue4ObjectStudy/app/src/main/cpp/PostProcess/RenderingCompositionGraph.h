//
// Created by liuqian8 on 2019/1/28.
//

//后期渲染框架的核心，本质上是一个DAG（有向无循环图）的实现
//有向无循环图解释：https://baike.baidu.com/item/有向无环图/10972513?fr=aladdin
#pragma once
#include <string>
#include <vector>
#include <Android/AndroidLog.h>
#include "PostProcessParameters.h"
using namespace std;


struct RenderingCompositeOutput;
struct RenderingCompositeOutputRef;
struct RenderingCompositePass;

class RenderingCompositionGraph
{
public:
    RenderingCompositionGraph();

    ~RenderingCompositionGraph();

    template<class T> T* RegisterPass(T* InPass)
    {
        Nodes.push_back(InPass);
        LOGE("nodes length:%d",Nodes.size());
        return InPass;
    }

    friend struct RenderingCompositePassContext;
private:
    std::vector<RenderingCompositePass*> Nodes;

    static void RecursivelyGatherDependencies(RenderingCompositePass* Pass);
    
};


struct RenderingCompositePassContext
{
    RenderingCompositePassContext();

    ~RenderingCompositePassContext();

    //call this only once after all nodes have been registered and connected (SetInput() or SetDependency())
    void Process(const vector<RenderingCompositePass*>& TargetRoots);

    void Process(RenderingCompositePass* Root)
    {
        vector<RenderingCompositePass*> TargetedRoots;
        TargetedRoots.push_back(Root);
        Process(TargetedRoots);
    }

    RenderingCompositionGraph Graph;

private:
    bool bWasProcessed;

};

//graph 的节点node
struct RenderingCompositePass
{
    RenderingCompositePass()
            :bComputeOutputDescWasCalled(false)
            ,bProcessWasCalled(false)
            ,bIsComputePass(false)
            ,bPreferAsyncCompute(false)
    {
    }

    virtual ~RenderingCompositePass(){}

    virtual RenderingCompositeOutputRef* GetInput(EPassInputId InPassInputId) = 0;

    virtual const RenderingCompositeOutputRef* GetInput(EPassInputId InPassInputId) const = 0;

    //Allows to iterate through all dependencies (inputs and additional dependency)
    virtual RenderingCompositeOutputRef* GetDependency(unsigned Index) = 0;

    //Allows to iterate through all additional dependencies
    virtual RenderingCompositeOutputRef* GetAdditionalDependency(unsigned Index) = 0;

    //return 0 if outside the range
    virtual RenderingCompositeOutput* GetOutput(EPassOutputId InPassOutputId) = 0;


protected:
    //to avoid wasteful recomputation and to support graph/DAG traversal, if ComputeOutputDesc() was called
    bool bComputeOutputDescWasCalled;
    //to allows reuse and to support graph/DAG traversal, if Process() was called
    bool bProcessWasCalled;

    bool bIsComputePass;
    bool bPreferAsyncCompute;

    friend class RenderingCompositionGraph;
};

struct RenderingCompositeOutputRef
{
    RenderingCompositeOutputRef(RenderingCompositePass* InSource = 0,EPassOutputId InPassOutputId = ePId_Output0)
            :Source(InSource),PassOutputId(InPassOutputId)
    {
    }

    RenderingCompositePass* GetPass()const;

    RenderingCompositeOutput* GetOutput() const;

    EPassOutputId GetOutputId() const { return PassOutputId;}

    bool IsValid() const
    {
        return Source != NULL;
    }


private:
    RenderingCompositePass* Source;

    EPassOutputId PassOutputId;

    friend class RenderingCompositionGraph;
};

struct RenderingCompositeOutput
{
    RenderingCompositeOutput():
            Dependencies(0)
    {
    }

    void ResetDependency()
    {
        Dependencies = 0;
    }

    void AddDependency()
    {
        ++Dependencies;
        LOGE("DAG %d:",Dependencies);
    }

    unsigned GetDependencyCount() const
    {
        return Dependencies;
    }

    void ResolveDependencies()
    {
        if(Dependencies > 0)
        {
            --Dependencies;
            if(!Dependencies)
            {
                //回收该节点的渲染目标RenderTarget //the internal reference is released

            }
        }
    }


private:
    unsigned Dependencies;
};

template <unsigned InputCount,unsigned OutPutCount> struct RenderingCompositePassBase:public RenderingCompositePass
{
    RenderingCompositePassBase()
    {
//        for(unsigned i = 0; i < OutPutCount; ++i)
//        {
//        }
    }

    virtual RenderingCompositeOutputRef* GetInput(EPassInputId InPassInputId)
    {
        if((unsigned)InPassInputId < InputCount)
        {
            return &PassInputs[InPassInputId];
        }
        return 0;
    }

    virtual const RenderingCompositeOutputRef* GetInput(EPassInputId InPassInputId) const
    {
        if((unsigned)InPassInputId < InputCount)
        {
            return &PassInputs[InPassInputId];
        }
        return 0;
    }

    virtual RenderingCompositeOutputRef* GetDependency(unsigned Index)
    {
        RenderingCompositeOutputRef* Ret = GetInput((EPassInputId)Index);
        if(!Ret)
        {
            Ret = GetAdditionalDependency(Index - InputCount);
        }
        return Ret;
    }

    RenderingCompositeOutputRef* GetAdditionalDependency(unsigned Index)
    {
        unsigned AdditionalDependenciesCount = AdditionalDependencies.size();

        if(Index < AdditionalDependenciesCount)
        {
            return &AdditionalDependencies[Index];
        }

        return 0;
    }

    virtual RenderingCompositeOutput* GetOutput(EPassOutputId InPassOutputId)
    {
        if((unsigned)InPassOutputId < OutPutCount)
        {
            return &PassOutputs[InPassOutputId];
        }
        return 0;
    }

private:
    vector<RenderingCompositeOutputRef> AdditionalDependencies;
    /** use GetInput() instead of accessing PassInputs directly */
    RenderingCompositeOutputRef PassInputs[InputCount == 0 ? 1 : InputCount];

protected:
    RenderingCompositeOutput PassOutputs[OutPutCount];
};


