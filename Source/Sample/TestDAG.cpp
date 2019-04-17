//
// Created by liuqian8 on 2019/2/21.
//
#include "TestDAG.h"

TestDAG::TestDAG()
{
    PassDag_ = new RenderingCompositionGraph();
}

TestDAG::~TestDAG()
{
    if(PassDag_)
    {
        delete PassDag_ ;
    }
}

