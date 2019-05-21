//
// Created by liuqian8 on 2019/4/17.
//
#include "transform.hpp"
#include <glm/ext.hpp>
#include "ObjSample.h"
#include "File.h"
#include <math.h>
ObjSample::ObjSample():
    Context_(NULL),
    PositionHandle_(0),
    TexcoordHandle_(0),
    MVPMatrixHandle_(0)
{

}

ObjSample::~ObjSample()
{

}

void ObjSample::CreateScence(Context *context, int width, int height)
{
    Context_ = context;
    glViewport(0,0,width,height);
    File* file = new File(Context_);
    std::string vertexShaderSource = file->getStringFromFileAssets("PBRVertex.glsl");
    std::string fragShaderSource = file->getStringFromFileAssets("PBRFragment.glsl");
    glProgram = new GLProgram();
    glProgram->initWithVertexShaderString(vertexShaderSource,fragShaderSource);
    glProgram->addAttribute("position");
    glProgram->addAttribute("texCoord");
    glProgram->addAttribute("normal");
    glProgram->link();
    PositionHandle_ = glProgram->getAttributeIndex("position");
    TexcoordHandle_ = glProgram->getAttributeIndex("texCoord");
    NormalHandle_ = glProgram->getAttributeIndex("normal");
    MVPMatrixHandle_ = glProgram->getUniformIndex("uMVPMatix");
    TextureHandle_ = glProgram->getUniformIndex("DefaultTexture");

    LOGI("TextureHandle_:%d",TextureHandle_);
    loadObj_ = new LoadObj();

    bool loadout = loadObj_->LoadFile("/sdcard/PBRObj/Fish/fish.obj");// Fish/fish.obj   Box/box_stack.obj  Persion/Model.obj  Test/Hyena_OBJ.obj
    if(loadout)
    {
        LOGI("obj加载成功！");
    }else{
        LOGE("obj加载失败！");
    }

    MVPMatrix_ = glm::mat4(1.0);
    ModelMatrix_ = glm::mat4(1.0);
    CameraMatrix_ = glm::mat4(1.0);
    ProjectMatrix_ = glm::mat4(1.0);

    float pi = 3.1415926f;

    ModelMatrix_ = glm::translate(glm::vec3(0,-1,-5))*glm::rotate(pi/2.f,glm::vec3(0,1,0))* glm::rotate(pi/1.f,glm::vec3(1,0,0))*glm::scale(glm::vec3(0.05,0.05,0.05));
    CameraMatrix_ = glm::lookAt(glm::vec3(5,1,-1),glm::vec3(0,-1,-1),glm::vec3(0,1,0));
    ProjectMatrix_ = glm::frustumRH(-1,1,-1,1,1,1000);

    MVPMatrix_ = ProjectMatrix_*CameraMatrix_* ModelMatrix_;
    textureId_ = context->getTextureId("fish");
}

void ObjSample::Move()
{
    float pi = 3.1415926f;
    ModelMatrix_ = glm::translate(glm::vec3(-2,-3,-5));
    float angle = count * (pi/50);
    ModelMatrix_ = ModelMatrix_ * glm::rotate(angle,glm::vec3(0,1,0));
    ModelMatrix_ = ModelMatrix_ * glm::scale(glm::vec3(0.05,0.05,0.05));

    MVPMatrix_ = ProjectMatrix_*CameraMatrix_* ModelMatrix_;
    count ++;
}

void ObjSample::RenderOneFrame(Context *context)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glProgram->use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId_);
    glUniform1i(TextureHandle_,0);


    glEnableVertexAttribArray(PositionHandle_);
    glEnableVertexAttribArray(TexcoordHandle_);
    glEnableVertexAttribArray(NormalHandle_);

    glVertexAttribPointer(PositionHandle_, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), loadObj_->LoadedVertices.data());
    glVertexAttribPointer(NormalHandle_, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (reinterpret_cast<char*>(loadObj_->LoadedVertices.data()) + 3 * sizeof(GL_FLOAT)));
    glVertexAttribPointer(TexcoordHandle_, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (reinterpret_cast<char*>(loadObj_->LoadedVertices.data()) + 6 * sizeof(GL_FLOAT)));

    glUniformMatrix4fv(MVPMatrixHandle_, 1, false, (GLfloat *)&MVPMatrix_);
    glDrawElements(GL_TRIANGLES, loadObj_->LoadedIndices.size(),GL_UNSIGNED_INT,loadObj_->LoadedIndices.data());

    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
    glDisable(GL_DEPTH_TEST);
}
