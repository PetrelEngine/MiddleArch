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
    glProgram->link();
    PositionHandle_ = glProgram->getAttributeIndex("position");
    MVPMatrixHandle_ = glProgram->getUniformIndex("uMVPMatix");

    loadObj_ = new LoadObj();

    bool loadout = loadObj_->LoadFile("/sdcard/PBRObj/Box/box_stack.obj");
    if(loadout)
    {
        LOGI("obj加载成功！");
    }else{
        LOGE("obj加载失败！");
    }

    Mesh mesh = loadObj_->LoadedMeshes[0];
    vertexList = mesh.Vertices;
    indexList = mesh.Indices;
    LOGE("indexList:%d",indexList.size());
    indexPointer_ = new int[indexList.size()];
    for(int i =0;i < indexList.size();i++)
    {
        indexPointer_[i] = indexList[i];
    }
    Position = new float[vertexList.size() * 3];
    for(int i = 0; i < vertexList.size(); i++)
    {
        Position[i * 3 + 0] = vertexList[i].Position.X;
        Position[i * 3 + 1] = vertexList[i].Position.Y;
        Position[i * 3 + 2] = vertexList[i].Position.Z;
    }


    MVPMatrix_ = glm::mat4(1.0);
    ModelMatrix_ = glm::mat4(1.0);
    CameraMatrix_ = glm::mat4(1.0);
    ProjectMatrix_ = glm::mat4(1.0);

    float pi = 3.1415926f;
//    ModelMatrix_ = glm::translate(glm::vec3(1,0,-150))*glm::rotate(pi/4.0f,glm::vec3(1,0,0))*glm::scale(glm::vec3(0.1,0.1,0.1));

    ModelMatrix_ = glm::translate(glm::vec3(0,-1,-1))*glm::rotate(pi/4.0f,glm::vec3(0,1,0))* glm::rotate(pi/4.0f,glm::vec3(1,0,0));//*glm::scale(glm::vec3(0.5,0.5,0.5));
    CameraMatrix_ = glm::lookAt(glm::vec3(0,0,2),glm::vec3(0,0,0),glm::vec3(0,1,0));
    ProjectMatrix_ = glm::frustumRH(-1,1,-1,1,1,1000);

    MVPMatrix_ = ProjectMatrix_*CameraMatrix_* ModelMatrix_;
}

void PBRSample::RenderOneFrame(Context *context)
{
    glProgram->use();

    glEnableVertexAttribArray(PositionHandle_);
    glCullFace(GL_CCW);
    
    glVertexAttribPointer(PositionHandle_, 3, GL_FLOAT, GL_FALSE, 0, Position);
    glUniformMatrix4fv(MVPMatrixHandle_, 1, false, (GLfloat *)&MVPMatrix_);
    glDrawElements(GL_TRIANGLES, 36,GL_UNSIGNED_INT,indexPointer_);

    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
}
