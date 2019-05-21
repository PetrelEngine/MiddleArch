//
// Created by liuqian8 on 2019/5/21.
//
#pragma once
#include "Context.h"

class PBR_lighting
{
public:
    PBR_lighting();

    ~PBR_lighting();

    void CreateScence(Context* context,int width,int height);

    void RenderScence();

protected:

};
