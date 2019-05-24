//
// Created by liuqian8 on 2019/5/24.
//
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(Context* context):
    Object(context),
    GPUObject(getSubsystem<Graphics>()),
    indexCount_(0),
    indexSize_(0),
    dynamic_(false)
{
}

IndexBuffer::~IndexBuffer()
{

}

bool IndexBuffer::SetSize(unsigned indexCount, bool largeIndices, bool dynamic)
{

    return true;
}

bool IndexBuffer::SetData(const void *data)
{
    
}

bool IndexBuffer::Create()
{

    return true;
}

bool IndexBuffer::UpdateToGPU()
{

}
