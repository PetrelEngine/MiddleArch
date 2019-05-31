//
// Created by liuqian8 on 2019/5/23.
//
#include "Geometry.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Graphics.h"
Geometry::Geometry(Context* context):
    Object(context),
    primitiveType_(TRIANGLE_LIST),
    indexStart_(0),
    indexCount_(0),
    vertexStart_(0),
    vertexCount_(0)
{
    vertexBuffers_.resize(1);
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
    vertexCount_ = buffer->GetVertexCount();
    return true;
}

void Geometry::SetIndexBuffer(IndexBuffer *buffer)
{
    indexBuffer_ = buffer;
    indexCount_ = indexBuffer_->GetIndexCount();

}

bool Geometry::SetDrawRange(PrimitiveType type, unsigned indexStart, unsigned indexCount,bool getUsedVertexRange)
{

    return true;
}

bool Geometry::SetDrawRange(PrimitiveType type, unsigned indexStart, unsigned indexCount,unsigned vertexStart, unsigned vertexCount, bool checkIllegal)
{

    return true;
}

void Geometry::Draw(Graphics *graphics)
{
    if(indexBuffer_ && indexCount_ > 0)//索引法绘制
    {
        graphics->SetIndexBuffer(indexBuffer_);
        graphics->SetVertexBuffers(vertexBuffers_);
        graphics->Draw(primitiveType_,indexStart_,indexCount_,vertexStart_,vertexCount_);
    }else if(vertexCount_ > 0)//三角形卷绕法
    {
        graphics->SetVertexBuffers(vertexBuffers_);
        graphics->Draw(primitiveType_, vertexStart_,vertexCount_);
    }
}
