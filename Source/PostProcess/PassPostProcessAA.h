//
// Created by liuqian8 on 2019/2/21.
//

#pragma once

#include "RenderingCompositionGraph.h"

class PassPostProcessAA: public RenderingCompositePassBase<1,1>
{
public:
    PassPostProcessAA();
    virtual ~PassPostProcessAA();
};
