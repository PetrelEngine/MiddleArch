//
// Created by liuqian8 on 2019/5/23.
//
#pragma once

#include <vector>
#include "Object.h"
#include "GPUObject.h"
#include "DataStruct.h"

class VertexBuffer: public Object,public GPUObject
{
    ENGINE_OBJECT(VertexBuffer,Object);
public:
    VertexBuffer(Context* context);

    ~VertexBuffer();

    bool SetSize(unsigned vertexCount, const std::vector<VertexElement>& elements,bool dynamic = false);

    bool setData(const void* data);

    unsigned GetVertexCount() const {return vertexCount_;}

    unsigned GetVertexSize()const {return vertexSize_;}

    std::vector<VertexElement> GetElements() const {return elements_;}

protected:


private:
    void UpdateOffsets();

    bool Create();

    unsigned vertexCount_;

    unsigned vertexSize_;

    std::vector<VertexElement> elements_;

    bool dynamic_;
};
