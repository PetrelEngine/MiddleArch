//
// Created by liuqian8 on 2019/5/6.
//
#pragma once
#include "RenderingCompositionGraph.h"

//后期渲染控制模块
//the context used to setup a post-process pass
class PostprocessContext
{
public:
    PostprocessContext(RenderingCompositionGraph& InGraph);

    RenderingCompositionGraph& Graph;
    RenderingCompositePass* SceneDepth;
    RenderingCompositeOutputRef FinalOutput;
};


class PostProcessing
{
public:

};
