//
// Created by liuqian8 on 2019/5/24.
//
#pragma once

#include "Object.h"
#include "GPUObject.h"

class IndexBuffer: public Object, public GPUObject
{
    ENGINE_OBJECT(IndexBuffer,Object);
public:
    IndexBuffer(Context* context);

    ~IndexBuffer();

    bool SetSize(unsigned indexCount,bool largeIndices,bool dynamic = false);

    bool SetData(const void* data);

    unsigned GetIndexCount() const {return indexCount_;}

    unsigned GetIndexSize() const {return indexSize_;}

private:
    bool Create();

    bool UpdateToGPU();

    unsigned indexCount_;

    unsigned indexSize_;

    bool dynamic_;
};
