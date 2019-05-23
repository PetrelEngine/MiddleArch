//
// Created by liuqian8 on 2019/5/23.
//
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(Context* context):
    Object(context),
    GPUObject(getSubsystem<Graphics>())
{

}

VertexBuffer::~VertexBuffer()
{

}

void VertexBuffer::setData(const void *data)
{

}

bool VertexBuffer::Create()
{
    if(!vertexCount_)
    {
       return false;
    }

    if(graphics_)
    {
        if(!object_.name_)
        {
            glGenBuffers(1,&object_.name_);
        }

        if(!object_.name_)
        {
            LOGE("Failed to create vertex buffer.");
            return false;
        }
        graphics_->SetVBO(object_.name_);
        //暂时性设置为静态的形式，后面拓展
        glBufferData(GL_ARRAY_BUFFER, vertexCount_ * vertexSize_, nullptr, GL_STATIC_DRAW);
    }
    return true;
}