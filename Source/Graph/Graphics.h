//
// Created by liuqian8 on 2019/5/23.
//
#pragma once
#include "Object.h"
#include "DataStruct.h"
#include "ShaderVariation.h"
#include <vector>
class IndexBuffer;
class GPUObject;
class VertexBuffer;
class GraphicsImpl;
class Graphics: public Object
{
    ENGINE_OBJECT(Graphics,Object);
public:

    Graphics(Context* context);

    ~Graphics();
    //设置VBo的id
    void SetVBO(unsigned object);

    void SetIndexBuffer(IndexBuffer* buffer);

    void SetVertexBuffer(VertexBuffer* vertexBuffer);

    bool SetVertexBuffers(const std::vector<VertexBuffer*> buffers, unsigned instanceOffset = 0);

    void SetShaders(ShaderVariation* vs, ShaderVariation* ps);
    //三角形卷绕绘制
    void Draw(PrimitiveType type, unsigned vertexStart, unsigned vertexCount);
    //索引法绘制
    void Draw(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned minVertex, unsigned vertexCount);

private:
    /// Process dirtied state before draw.
    void PrepareDraw();

    void GetGLPrimitiveType(unsigned elementCount, PrimitiveType type, unsigned& primitiveCount, GLenum& glPrimitiveType);
    IndexBuffer* indexBuffer_;
    VertexBuffer* vertexBuffers_[MAX_VERTEX_STREAMS];
    GraphicsImpl* impl_;
    /// Vertex shader in use.
    ShaderVariation* vertexShader_;
    /// Pixel shader in use.
    ShaderVariation* pixelShader_;
protected:

};
