//
// Created by liuqian8 on 2019/4/22.
//

#pragma once
#include "GPUObject.h"
#include "Object.h"

class VertexBuffer : public Object,public GPUObject
{
ENGINE_OBJECT(VertexBuffer,Object);
public:
    VertexBuffer(Context* context,bool forceHeadless = false);

    ~VertexBuffer();
};
