//
// Created by liuqian8 on 2019/4/17.
//
#pragma once

#include <Mesh/LoadObj.h>
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

    LoadObj*                    loadObj_;

    ShaderProgram*              ShaderProgram_;

    std::vector<float>          PositionData_;
    std::vector<float>          TexCoordData_;
    std::vector<float>          NormalData_;
    int*                        IndexData_;


    unsigned                    TextureHandle_;
    unsigned                    PositionHandle_;
    unsigned                    MVPMatrixHandle_;
    unsigned                    TexcoordHandle_;
    unsigned                    NormalHandle_;

    glm::mat4                   ModelMatrix_;
    glm::mat4                   CameraMatrix_;
    glm::mat4                   ProjectMatrix_;
    glm::mat4                   MVPMatrix_;
};
