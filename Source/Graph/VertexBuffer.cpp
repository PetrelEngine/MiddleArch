//
// Created by liuqian8 on 2019/5/23.
//
#include "VertexBuffer.h"
#include "Graphics.h"
VertexBuffer::VertexBuffer(Context* context):
    Object(context),
    GPUObject(getSubsystem<Graphics>()),
    vertexCount_(0),
    dynamic_(0)
{

}

VertexBuffer::~VertexBuffer()
{

}

bool VertexBuffer::SetSize(unsigned vertexCount, const std::vector<VertexElement> &elements,bool dynamic)
{
    vertexCount_ = vertexCount;
    elements_    = elements;
    dynamic_     = dynamic;

    UpdateOffsets();

    return Create();
}

bool VertexBuffer::setData(const void *data)
{
    if(!data)
    {
        LOGE("Null pointer for vertex buffer data.");
        return false;
    }

    if(!vertexSize_)
    {
        LOGE("Vertex elements not defined, can not set vertex buffer data.");
        return false;
    }

    if(object_.name_)
    {
        graphics_->SetVBO(object_.name_);
        glBufferData(GL_ARRAY_BUFFER,vertexCount_ * vertexSize_,data,dynamic_?GL_DYNAMIC_DRAW:GL_STATIC_DRAW);
    }

    dataLost_ = false;

    return true;
}

void VertexBuffer::UpdateOffsets()
{
    unsigned elementOffset = 0;
    for(int i = 0; i < elements_.size(); i ++)
    {
        VertexElement vertexElement = elements_[i];
        vertexElement.offset_ = elementOffset;
        elementOffset += ELEMENT_TYPESIZE[vertexElement.type_];
    }
    vertexSize_ = elementOffset;
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
        glBufferData(GL_ARRAY_BUFFER, vertexCount_ * vertexSize_, nullptr, dynamic_?GL_DYNAMIC_DRAW:GL_STATIC_DRAW);
    }
    return true;
}