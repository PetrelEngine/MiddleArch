//
// Created by liuqian8 on 2019/4/22.
//

#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(Context *context, bool forceHeadless):
    Object(context),
    GPUObject(forceHeadless?NULL:getSubsystem<Graphics>())
{

}

VertexBuffer::~VertexBuffer()
{

}