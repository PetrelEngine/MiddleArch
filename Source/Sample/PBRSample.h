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
    Context* Context_;

    LoadObj* loadObj_;

    ShaderProgram* ShaderProgram_;

    unsigned TextureHandle_;
    unsigned PositionHandle_;
    unsigned MVPMatrixHandle_;
    unsigned TexcoordHandle_;
};
