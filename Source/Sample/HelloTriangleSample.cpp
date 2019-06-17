//
// Created by liuqian8 on 2019/5/29.
//
#include <glm/ext.hpp>
#include "HelloTriangleSample.h"
#include "Graphics.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "DataStruct.h"
#include "View.h"
#include "ShaderProgram.h"
#include "ShaderVariation.h"
#include "Shader.h"
#include "Geometry.h"

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
    File_ = Context_->getSubsystem<File>();
    std::string vertexShaderSource = File_->getStringFromFileAssets("Shader/BaseVertex.glsl");
    std::string fragShaderSource = File_->getStringFromFileAssets("Shader/BaseFragment.glsl");

    Shader* shader_ = new Shader(context);
    shader_->SetShaderSourceCode(VS,vertexShaderSource);
    shader_->SetShaderSourceCode(PS,fragShaderSource);
    ShaderVariation* vertexShader_ = new ShaderVariation(shader_,VS);
    ShaderVariation* fragmentShader_ = new ShaderVariation(shader_,PS);

    //组建顶点几何数据
    VertexBuffer* vertexBuffer_ = new VertexBuffer(context);
//    indexBuffer_ = new IndexBuffer(context);
    Geometry* geometry_ = new Geometry(context);
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

    camera_ = new Camera(context);
    camera_->setAspectRadio((float)width/(float)height);

    view_ = new View(context);

    batch_.geometry_ = geometry_;
    batch_.vertexShader_ = vertexShader_;
    batch_.pixelShader_ = fragmentShader_;
    batch_.modelmatrix_ = glm::translate(glm::vec3(0,-1,-3))*glm::rotate(0.0f,glm::vec3(0,1,0))* glm::rotate(0.0f,glm::vec3(1,0,0))*glm::scale(glm::vec3(2.0f,2.0f,2.0f));
}

void HelloTriangleSample::RenderOneFrame(Context *context)
{
    batch_.Draw(view_,camera_);
}

void HelloTriangleSample::Move()
{

}
