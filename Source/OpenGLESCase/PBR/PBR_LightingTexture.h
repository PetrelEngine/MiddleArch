//
// Created by liuqian8 on 2019/5/21.
//
#pragma once

#include "RectData.h"
#include "GLProgram.hpp"
#include "File.h"
#include "Context.h"
#include "Sphere.h"
#include "GraphPBR.h"
#include "Texture2D.h"
class PBR_LightingTexture
{
public:
    PBR_LightingTexture();

    ~PBR_LightingTexture();

    void CreateScence(Context* context,int width,int height);

    void RenderScence();

    void move();

protected:
    Sphere*                     Sphere_;
    Context*                    Context_;
    File*                       File_;
    GLProgram*                  GLProgram_;
    PRBGraph                    PRBGraph_;
    int                         count = 0;

    Texture2D*  albedo_;
    Texture2D*  ao_;
    Texture2D*  metallic_;
    Texture2D*  normal_;
    Texture2D*  roughness_;
};
