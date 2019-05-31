//
// Created by liuqian8 on 2019/5/23.
//
#pragma once
#include "Object.h"
#include "DataStruct.h"
#include <vector>
#include "Common.h"
class Graphics;
class IndexBuffer;
class VertexBuffer;
class Geometry:public Object
{
    ENGINE_OBJECT(Geometry,Object);
public:
    Geometry(Context* context);
    ~Geometry();

    /// Set a vertex buffer by index.
    bool SetVertexBuffer(unsigned index, VertexBuffer* buffer);

    void SetIndexBuffer(IndexBuffer* buffer);
    /// Set the draw range.
    bool SetDrawRange(PrimitiveType type, unsigned indexStart, unsigned indexCount, bool getUsedVertexRange = true);
    /// Set the draw range.
    bool SetDrawRange(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned vertexStart, unsigned vertexCount, bool checkIllegal = true);

    void Draw(Graphics* graphics);

protected:

private:
    IndexBuffer* indexBuffer_;
    std::vector<VertexBuffer*> vertexBuffers_;
    PrimitiveType primitiveType_;
    unsigned indexStart_;
    unsigned indexCount_;
    unsigned vertexStart_;
    unsigned vertexCount_;
};
