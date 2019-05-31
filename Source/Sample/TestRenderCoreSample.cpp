//
// Created by liuqian8 on 2019/5/29.
//
#include "TestRenderCoreSample.h"
#include "Graphics.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "DataStruct.h"
TestRenderCoreSample::TestRenderCoreSample()
{

}

TestRenderCoreSample::~TestRenderCoreSample()
{
    if(File_)
    {
        delete File_;
        File_ = NULL;
    }
}

void TestRenderCoreSample::CreateScence(Context *context, int width, int height)
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
            0.0f, 1.0f,  0.0f,  0.0f, 1.0f, 0.0f,   0.5f,  1.0f,
            -1.0f,-1.0f, 0.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
            1.0f, 1.0f,  0.0f,  0.0f, 1.0f, 0.0f,   1.0f,  0.0f,
    };
    std::vector<VertexElement> elements;
    VertexElement pos ={TYPE_VECTOR3,SEM_POSITION,"iPos",0};
    VertexElement normal ={TYPE_VECTOR3,SEM_NORMAL,"iNormal",0};
    VertexElement texcoord ={TYPE_VECTOR2,SEM_TEXCOORD,"iTexCoord",0};
    LOGE("Create 5");
    elements.push_back(pos);
    elements.push_back(normal);
    elements.push_back(texcoord);
    vertexBuffer_->SetSize(3,elements);
    LOGE("Create 6");
    vertexBuffer_->setData(vertex);
//    geometry_->SetIndexBuffer(indexBuffer_);
    LOGE("Create 7");
    geometry_->SetVertexBuffer(0,vertexBuffer_);
    LOGE("CreateEnd");
}

void TestRenderCoreSample::RenderOneFrame(Context *context)
{
    LOGE("preDraw");
    geometry_->Draw(graphics_);
    LOGE("endDraw");
}

void TestRenderCoreSample::Move()
{

}
