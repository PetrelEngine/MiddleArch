//
// Created by liuqian8 on 2019/5/23.
//
#include "Geometry.h"

Geometry::Geometry()
{

}

Geometry::~Geometry()
{

}

bool Geometry::SetVertexBuffer(unsigned index, VertexBuffer *buffer)
{
    if(index >= vertexBuffers_.size())
    {
        LOGE("Stream index out of bounds");
        return false;
    }
    vertexBuffers_[index] = buffer;
    return true;
}

void Geometry::SetIndexBuffer(IndexBuffer *buffer)
{
    indexBuffer_ = buffer;
}

void Geometry::Draw(Graphics *graphics)
{
//    if(indexBuffer_)
//    {
//
//    }else if()
//    {
//
//    }
}
