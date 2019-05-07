//
// Created by liuqian8 on 2019/4/17.
//
#pragma once

#include "WBGLProgram.hpp"
#include "LoadObj.h"
#include "Application.h"
#include "Common.h"
#include "type_mat.hpp"
#include "type_mat4x4.hpp"
class PBRSample: public Application
{
public:
    PBRSample();
    ~PBRSample();

    void move();

    virtual void CreateScence(Context* context,int width,int height);

    virtual void RenderOneFrame(Context* context);

private:
    Context*                    Context_;
    WBGLProgram*                glProgram;
    LoadObj*                    loadObj_;
    int                         textureId_;

    GLuint                      PositionHandle_;
    GLuint                      MVPMatrixHandle_;
    GLuint                      TexcoordHandle_;
    GLuint                      NormalHandle_;

    GLuint                      TextureHandle_;

    glm::mat4                   ModelMatrix_;
    glm::mat4                   CameraMatrix_;
    glm::mat4                   ProjectMatrix_;
    glm::mat4                   MVPMatrix_;

    int count = 0;
};
