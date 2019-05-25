//
// Created by liuqian8 on 2019/5/23.
//
#include "Graphics.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"

Graphics::Graphics(Context* context):
Object(context)
{

}

Graphics::~Graphics()
{

}

void Graphics::SetIndexBuffer(IndexBuffer *buffer)
{
    if(indexBuffer_ == buffer)
        return;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer ? buffer->getGPUObjectName() : 0);
    indexBuffer_ = buffer;
}

void Graphics::SetVBO(unsigned object)
{
    if(object)
        glBindBuffer(GL_ARRAY_BUFFER,object);
}
//三角形卷绕绘制
void Graphics::Draw(PrimitiveType type, unsigned vertexStart, unsigned vertexCount)
{

}
//索引法绘制
void Graphics::Draw(PrimitiveType type, unsigned indexStart, unsigned indexCount,unsigned minVertex, unsigned vertexCount)
{

}
