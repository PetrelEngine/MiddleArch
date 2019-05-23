//
// Created by liuqian8 on 2019/5/23.
//
#pragma once

#include "Object.h"
#include "GPUObject.h"

class VertexBuffer: public Object,public GPUObject
{
    ENGINE_OBJECT(VertexBuffer,Object);
public:
    VertexBuffer(Context* context);
    ~VertexBuffer();

    void setData(const void* data);

protected:


private:
    bool Create();

    unsigned vertexCount_;
    unsigned vertexSize_;
};
