//
// Created by liuqian8 on 2019/4/29.
//
#pragma once

#include "Context.h"
#include "RenderResource.h"

class VertexBuffer:public RenderResource
{
public:
    VertexBuffer(Context* context);
    virtual ~VertexBuffer();

    void Release();


protected:
    Context* context_;
};
