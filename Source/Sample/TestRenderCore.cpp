//
// Created by liuqian8 on 2019/5/29.
//
#include "TestRenderCore.h"
#include "Graphics.h"
TestRenderCore::TestRenderCore()
{

}

TestRenderCore::~TestRenderCore()
{
    if(File_)
    {
        delete File_;
        File_ = NULL;
    }
}

void TestRenderCore::testShader(Context *context)
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

    GL_FLOAT

    context->getSubsystem<Graphics>()->SetShaders(vertexShader_,fragmentShader_);
}
