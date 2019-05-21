//
// Created by liuqian8 on 2019/5/20.
//

#pragma once

#include "GLProgram.hpp"
#include "File.h"
#include "Context.h"
#include "RectData.h"

struct GraphStencilTesting
{

};
class StencilTesting
{
public:
    StencilTesting();

    ~StencilTesting();

    void CreateScence(Context* context,int width,int height);

    void RenderScence();

protected:
    Context*                    Context_;
    File*                       File_;
    Rect3D*                     Rect3D_;
    GLProgram*                GLProgram__;
    GraphStencilTesting         GraphStencilTesting_;
};
