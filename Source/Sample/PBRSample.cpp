//
// Created by liuqian8 on 2019/4/17.
//
#include "PBRSample.h"
#include "File.h"
PBRSample::PBRSample():
    Context_(NULL),
    loadObj_(NULL),
    ShaderProgram_(NULL)
{

}

PBRSample::~PBRSample()
{

}

void PBRSample::CreateScence(Context *context, int width, int height)
{
    Context_ = context;

    File* file = new File(Context_);

    std::string vertexShaderSource = file->getStringFromFileAssets("PBRVertex.glsl");
    std::string fragShaderSource = file->getStringFromFileAssets("PBRFragment.glsl");

    loadObj_ = new LoadObj();
    bool loadout = loadObj_->LoadFile("/sdcard/PBRObj/Box/box_stack.obj");
    if(loadout)
    {
        LOGI("OBJ模型加载成功。");
    }else{
        LOGI("OBJ模型加载失败。");
    }
    glViewport(0,0,width,height);

    ShaderProgram_ = new ShaderProgram(vertexShaderSource,fragShaderSource);

    PositionHandle_ = ShaderProgram_->getAttribLocation("position");
    TexcoordHandle_ = ShaderProgram_->getAttribLocation("texCoord");
    TextureHandle_ = ShaderProgram_->getUniformLocation("DefaultTexture");
    MVPMatrixHandle_ = ShaderProgram_->getUniformLocation("uMVPMatix");
    glUseProgram(ShaderProgram_->ID);
    glEnableVertexAttribArray(PositionHandle_);
    glEnableVertexAttribArray(TexcoordHandle_);

}

void PBRSample::RenderOneFrame(Context *context)
{

}
