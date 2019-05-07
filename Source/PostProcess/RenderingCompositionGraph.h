//
// Created by liuqian8 on 2019/1/28.
//

//后期渲染框架的核心，本质上是一个DAG（有向无循环图）的实现
//有向无循环图解释：https://baike.baidu.com/item/有向无环图/10972513?fr=aladdin
#pragma once
#include <string>
#include <vector>
#include "Common.h"
#include "PostProcessParameters.h"
using namespace std;


struct RenderingCompositeOutput;
struct RenderingCompositeOutputRef;
struct RenderingCompositePass;
struct RenderingCompositePassContext;

class RenderingCompositionGraph
{
public:
    RenderingCompositionGraph();

    ~RenderingCompositionGraph();

    template<class T> T* RegisterPass(T* InPass)
    {
        Nodes.push_back(InPass);
        LOGI("nodes length:%d",Nodes.size());
        return InPass;
    }

    friend struct RenderingCompositePassContext;
private:
    std::vector<RenderingCompositePass*> Nodes;

    static void RecursivelyGatherDependencies(RenderingCompositePass* Pass);
    /** could be implemented without recursion */
    void RecursivelyProcess(const RenderingCompositeOutputRef& InOutputRef, RenderingCompositePassContext& Context) const;
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

    // is updated before each Pass->Process() call
    RenderingCompositePass* Pass;

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

    /**
     * const version of GetInput()
     * @return 0 if outside the range
     */
    virtual RenderingCompositeOutputRef* GetInput(EPassInputId InPassInputId) = 0;

    virtual const RenderingCompositeOutputRef* GetInput(EPassInputId InPassInputId) const = 0;
    /**
     * Each input is a dependency and will be processed before the node itself (don't generate cycles)
     * The index allows to access the input in Process() and on the shader side
     * @param InInputIndex silently ignores calls outside the range
     */
    virtual void SetInput(EPassInputId InPassInputId, const RenderingCompositeOutputRef& InOutputRef) = 0;
    /**
     * Allows to add additional dependencies (cannot be accessed by the node but need to be processed before the node)
     */
    virtual void AddDependency(const RenderingCompositeOutputRef& InOutputRef) = 0;

    /** @param Parent the one that was pointing to *this */
    virtual void Process(RenderingCompositePassContext& Context) = 0;

    //Allows to iterate through all dependencies (inputs and additional dependency)
    virtual RenderingCompositeOutputRef* GetDependency(unsigned Index) = 0;

    //Allows to iterate through all additional dependencies
    virtual RenderingCompositeOutputRef* GetAdditionalDependency(unsigned Index) = 0;

    //return 0 if outside the range
    virtual RenderingCompositeOutput* GetOutput(EPassOutputId InPassOutputId) = 0;

//    virtual FPooledRenderTargetDesc ComputeOutputDesc(EPassOutputId InPassOutputId) const = 0;

    /** Convenience method as this could have been done with GetInput() alone, performance: O(n) */
    unsigned ComputeInputCount();

    /** Convenience method as this could have been done with GetOutput() alone, performance: O(n) */
    unsigned ComputeOutputCount();

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
        LOGI("DAG 0: %d:",Dependencies);
        ++Dependencies;
        LOGI("DAG 1: %d:",Dependencies);
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

template <unsigned InputCount,unsigned OutPutCount> struct RenderingCompositePassBase:public RenderingCompositePass {
    RenderingCompositePassBase() {
//        for(unsigned i = 0; i < OutPutCount; ++i)
//        {
//        }
        LOGI("InputCount:%d,  OutPutCount：%d", InputCount, OutPutCount);
    }

    virtual RenderingCompositeOutputRef *GetInput(EPassInputId InPassInputId) {
        if ((unsigned) InPassInputId < InputCount) {
            return &PassInputs[InPassInputId];
        }
        return 0;
    }

    virtual const RenderingCompositeOutputRef *GetInput(EPassInputId InPassInputId) const {
        if ((unsigned) InPassInputId < InputCount) {
            return &PassInputs[InPassInputId];
        }
        return 0;
    }

    virtual void SetInput(EPassInputId InPassInputId, const RenderingCompositeOutputRef& VirtualBuffer)
    {
        if((int)InPassInputId < InputCount)
        {
            PassInputs[InPassInputId] = VirtualBuffer;
        }else{
            //this node doesn't have this input.
            return;
        }
    }

    void AddDependency(const RenderingCompositeOutputRef& InOutputRef)
    {
        AdditionalDependencies.push_back(InOutputRef);
    }

    virtual void Process(RenderingCompositePassContext& Context)
    {

    }

    virtual RenderingCompositeOutput* GetOutput(EPassOutputId InPassOutputId)
    {
        LOGI("OutPutCount:%d",OutPutCount);
        if((unsigned)InPassOutputId < OutPutCount)
        {
            return &PassOutputs[InPassOutputId];
        }
        return 0;
    }

    virtual RenderingCompositeOutputRef* GetDependency(unsigned Index)
    {
        // first through all inputs
        RenderingCompositeOutputRef* Ret = GetInput((EPassInputId)Index);
        if(!Ret)
        {
            // then all additional dependencies
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

private:
    vector<RenderingCompositeOutputRef> AdditionalDependencies;
    /** use GetInput() instead of accessing PassInputs directly */
    RenderingCompositeOutputRef PassInputs[InputCount == 0 ? 1 : InputCount];

protected:
    RenderingCompositeOutput PassOutputs[OutPutCount];
};


