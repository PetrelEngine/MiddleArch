//
// Created by liuqian8 on 2019/5/23.
//

#pragma once

#include "Object.h"
#include "DataStruct.h"
class IndexBuffer;
class GPUObject;
class VertexBuffer;
class Graphics: public Object
{
    ENGINE_OBJECT(Graphics,Object);
public:

    Graphics(Context* context);

    ~Graphics();
    //设置VBo的id
    void SetVBO(unsigned object);

    void SetIndexBuffer(IndexBuffer* buffer);
    //三角形卷绕绘制
    void Draw(PrimitiveType type, unsigned vertexStart, unsigned vertexCount);
    //索引法绘制
    void Draw(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned minVertex, unsigned vertexCount);

private:
    IndexBuffer* indexBuffer_;
protected:

};
