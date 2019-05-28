//
// Created by liuqian8 on 2019/5/23.
//
#include "Graphics.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
static const unsigned glElementComponents[] =
{
        1,
        1,
        2,
        3,
        4,
        4,
        4
};
static const unsigned glElementTypes[] =
{
        GL_INT,
        GL_FLOAT,
        GL_FLOAT,
        GL_FLOAT,
        GL_FLOAT,
        GL_UNSIGNED_BYTE,
        GL_UNSIGNED_BYTE
};
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

void Graphics::SetVertexBuffer(VertexBuffer* vertexBuffer)
{
    std::vector<VertexBuffer*> vertexBuffers;
    vertexBuffers.push_back(vertexBuffer);
    SetVertexBuffers(vertexBuffers);
}

bool Graphics::SetVertexBuffers(const std::vector<VertexBuffer *> buffers,unsigned int instanceOffset)
{
    if(buffers.size() > 4)
    {
        LOGE("Too many vertex buffers.");
        return false;
    }
    for(unsigned i = 0; i < 4 ; i ++)
    {
        VertexBuffer* buffer = NULL;
        if(i < buffers.size())
            buffer = buffers[i];
        if(buffer != vertexBuffers_[i])
        {
            vertexBuffers_[i] = buffer;
        }
    }
    return true;
}

void Graphics::SetVBO(unsigned object)
{
    if(object)
        glBindBuffer(GL_ARRAY_BUFFER,object);
}
//三角形卷绕绘制
void Graphics::Draw(PrimitiveType type, unsigned vertexStart, unsigned vertexCount)
{
    if(!vertexCount)
        return;
    PrepareDraw();
    unsigned  primitiveCount;
    GLenum glPrimitiveType;

    GetGLPrimitiveType(vertexCount, type, primitiveCount, glPrimitiveType);

    glDrawArrays(glPrimitiveType, vertexStart, vertexCount);
}
//索引法绘制
void Graphics::Draw(PrimitiveType type, unsigned indexStart, unsigned indexCount,unsigned minVertex, unsigned vertexCount)
{
    if(!indexCount||indexBuffer_ || !indexBuffer_->getGPUObjectName())
        return;
    PrepareDraw();
}

void Graphics::PrepareDraw()
{
    //设置一个标识位，该操作只需要执行一次就可以了
    unsigned assignedLocations = 0;

    for(unsigned i = MAX_VERTEX_STREAMS - 1;i < MAX_VERTEX_STREAMS; i --)
    {
        VertexBuffer* buffer = vertexBuffers_[i];
        if(!buffer || !buffer->getGPUObjectName())
            continue;
        const std::vector<VertexElement> elements = buffer->GetElements();
        for(int j = 0 ; j < elements.size(); j ++)
        {
            VertexElement element = elements[j];
            GLuint location;
            glEnableVertexAttribArray(location);

            // Enable/disable instancing divisor as necessary
            unsigned dataStart = element.offset_;

            SetVBO(buffer->getGPUObjectName());
            glVertexAttribPointer(location,glElementComponents[element.type_],glElementTypes[element.type_],
                                  element.type_ == TYPE_UBYTE4_NORM ? GL_TRUE : GL_FALSE, (unsigned)buffer->GetVertexSize(),
                                  (const void *)(size_t)dataStart);
        }
    }
}

void Graphics::GetGLPrimitiveType(unsigned elementCount, PrimitiveType type,unsigned &primitiveCount, GLenum &glPrimitiveType)
{
    switch (type)
    {
        case TRIANGLE_LIST:
            primitiveCount = elementCount / 3;
            glPrimitiveType = GL_TRIANGLES;
            break;

        case LINE_LIST:
            primitiveCount = elementCount / 2;
            glPrimitiveType = GL_LINES;
            break;

        case POINT_LIST:
            primitiveCount = elementCount;
            glPrimitiveType = GL_POINTS;
            break;

        case TRIANGLE_STRIP:
            primitiveCount = elementCount - 2;
            glPrimitiveType = GL_TRIANGLE_STRIP;
            break;

        case LINE_STRIP:
            primitiveCount = elementCount - 1;
            glPrimitiveType = GL_LINE_STRIP;
            break;

        case TRIANGLE_FAN:
            primitiveCount = elementCount - 2;
            glPrimitiveType = GL_TRIANGLE_FAN;
            break;
    }
}
