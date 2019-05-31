//
// Created by liuqian8 on 2019/5/29.
//
#include "HelloTriangleSample.h"
#include "Graphics.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "DataStruct.h"
HelloTriangleSample::HelloTriangleSample()
{

}

HelloTriangleSample::~HelloTriangleSample()
{
    if(File_)
    {
        delete File_;
        File_ = NULL;
    }
}

void HelloTriangleSample::CreateScence(Context *context, int width, int height)
{
    Context_ = context;
    File_ = new File(Context_);
    std::string vertexShaderSource = File_->getStringFromFileAssets("Shader/BaseVertex.glsl");
    std::string fragShaderSource = File_->getStringFromFileAssets("Shader/BaseFragment.glsl");

    shader_ = new Shader(context);
    shader_->SetShaderSourceCode(VS,vertexShaderSource);
    shader_->SetShaderSourceCode(PS,fragShaderSource);
    vertexShader_ = new ShaderVariation(shader_,VS);
    fragmentShader_ = new ShaderVariation(shader_,PS);
    context->getSubsystem<Graphics>()->SetShaders(vertexShader_,fragmentShader_);
    graphics_ = context->getSubsystem<Graphics>();
    //组建顶点几何数据
    vertexBuffer_ = new VertexBuffer(context);
//    indexBuffer_ = new IndexBuffer(context);
    geometry_ = new Geometry(context);
    float vertex[] =
    {
            0.0f,  1.0f,  0.0f,  0.5f,  1.0f,   0.0f, 1.0f, 0.0f,
            -1.0f,-1.0f,  0.0f,  0.0f,  0.0f,   0.0f, 1.0f, 0.0f,
            1.0f, -1.0f,  0.0f,  1.0f,  0.0f,   0.0f, 1.0f, 0.0f,
    };
    std::vector<VertexElement> elements;

    elements.push_back(VertexElement(TYPE_VECTOR3,SEM_POSITION));
    elements.push_back(VertexElement(TYPE_VECTOR2,SEM_TEXCOORD));
    elements.push_back(VertexElement(TYPE_VECTOR3,SEM_NORMAL));

    vertexBuffer_->SetSize(3,elements);

    vertexBuffer_->setData(vertex);
//    geometry_->SetIndexBuffer(indexBuffer_);
    geometry_->SetVertexBuffer(0,vertexBuffer_);
}

void HelloTriangleSample::RenderOneFrame(Context *context)
{
    geometry_->Draw(graphics_);
}

void HelloTriangleSample::Move()
{

}
