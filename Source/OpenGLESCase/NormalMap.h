//
// Created by liuqian8 on 2019/5/22.
//
#pragma once

#include "GLProgram.hpp"
#include "File.h"
#include "Context.h"

class NormalMap
{
public:
    NormalMap();

    ~NormalMap();

    void CreateScence(Context* ,int width,int height);

    void RenderScence();

    void Move();
protected:
    Context*                    Context_;
    File*                       File_;
    GLProgram*                  GLProgram__;
};
