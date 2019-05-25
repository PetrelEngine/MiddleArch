//
// Created by liuqian8 on 2019/5/23.
//

#pragma once

#include "VertexBuffer.h"
class Graphics;
class IndexBuffer;
class Geometry
{
public:
    Geometry();
    ~Geometry();

    /// Set a vertex buffer by index.
    bool SetVertexBuffer(unsigned index, VertexBuffer* buffer);

    void SetIndexBuffer(IndexBuffer* buffer);

    void Draw(Graphics* graphics);

protected:

private:
    IndexBuffer* indexBuffer_;
    std::vector<VertexBuffer*> vertexBuffers_;
};
