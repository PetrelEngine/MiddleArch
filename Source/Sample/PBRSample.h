//
// Created by liuqian8 on 2019/4/17.
//
#pragma once

#include "WBGLProgram.hpp"
#include "LoadObj.h"
#include "ShaderProgram.h"
#include "Application.h"

class PBRSample: public Application
{
public:
    PBRSample();
    ~PBRSample();

    virtual void CreateScence(Context* context,int width,int height);

    virtual void RenderOneFrame(Context* context);

private:
    Context*                    Context_;
//    ShaderProgram*              ShaderProgram_;
    WBGLProgram*                glProgram;
    LoadObj*                    loadObj_;

    GLuint                      PositionHandle_;
    GLuint                      MVPMatrixHandle_;
    GLuint                      TexcoordHandle_;

    glm::mat4                   ModelMatrix_;
    glm::mat4                   CameraMatrix_;
    glm::mat4                   ProjectMatrix_;
    glm::mat4                   MVPMatrix_;

    std::vector<Vertex>         vertexList;
    std::vector<unsigned int>   indexList;
    int*                        indexPointer_;

    float*        Position;
    float*        TexCoord;
    float*        Normal;


};
