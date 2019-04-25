//
// Created by liuqian8 on 2019/4/17.
//
#include "transform.hpp"
#include <glm/ext.hpp>
#include "PBRSample.h"
#include "File.h"
#include <math.h>
PBRSample::PBRSample():
    Context_(NULL),
    PositionHandle_(0),
    TexcoordHandle_(0),
    MVPMatrixHandle_(0)
{

}

PBRSample::~PBRSample()
{

}

void PBRSample::CreateScence(Context *context, int width, int height)
{
    Context_ = context;
    glViewport(0,0,width,height);
    File* file = new File(Context_);
    std::string vertexShaderSource = file->getStringFromFileAssets("PBRVertex.glsl");
    std::string fragShaderSource = file->getStringFromFileAssets("PBRFragment.glsl");
    glProgram = new WBGLProgram();
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

    bool loadout = loadObj_->LoadFile("/sdcard/PBRObj/Fish/fish.obj");// Fish/fish.obj   Box/box_stack.obj
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

    ModelMatrix_ = glm::translate(glm::vec3(0,-1,-1))*glm::rotate(pi/4.f,glm::vec3(0,1,0))* glm::rotate(0.f,glm::vec3(1,0,0))*glm::scale(glm::vec3(0.1,0.1,0.1));
    CameraMatrix_ = glm::lookAt(glm::vec3(0,0,4),glm::vec3(0,0,0),glm::vec3(0,1,0));
    ProjectMatrix_ = glm::frustumRH(-1,1,-1,1,1,1000);

    MVPMatrix_ = ProjectMatrix_*CameraMatrix_* ModelMatrix_;

}

void PBRSample::RenderOneFrame(Context *context)
{
    glProgram->use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 1);
    glUniform1i(TextureHandle_,0);
    glCullFace(GL_CCW);
////    for(int i = 0; i < loadObj_->LoadedMeshes.size(); i ++)
////    {
//        glEnableVertexAttribArray(PositionHandle_);
//        glEnableVertexAttribArray(TexcoordHandle_);
//        glEnableVertexAttribArray(NormalHandle_);
//
////        Mesh mesh = loadObj_->LoadedMeshes[i];
////        std::vector<Vertex> Vertices = mesh.Vertices;
//
//        glVertexAttribPointer(PositionHandle_, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), loadObj_->LoadedVertices.data());
//        glVertexAttribPointer(TexcoordHandle_, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), loadObj_->LoadedVertices.data());
//        glVertexAttribPointer(NormalHandle_, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), loadObj_->LoadedVertices.data());
//
////        std::vector<unsigned int> index = mesh.Indices;
//        glUniformMatrix4fv(MVPMatrixHandle_, 1, false, (GLfloat *)&MVPMatrix_);
//        glDrawElements(GL_TRIANGLES, loadObj_->LoadedIndices.size(),GL_UNSIGNED_INT,loadObj_->LoadedIndices.data());
////    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
}