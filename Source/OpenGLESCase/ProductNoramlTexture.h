//
// Created by liuqian8 on 2019/5/13.
//
#pragma once

#include "GLProgram.hpp"
#include "File.h"
#include "Context.h"
#include "RectData.h"
#include "Texture2D.h"
class ProductNoramlTexture
{
public:
    ProductNoramlTexture();

    ~ProductNoramlTexture();

    void CreateScence(Context* context,int width,int height);

    void Renderer();

protected:
    bool SaveNormalTexture();

    Context*                    Context_;
    File*                       File_;
    GLuint                      u_ImageSizeHandle;
    GLuint                      u_ImageHandle;
    GLuint                      u_PositionHandle;
    GLuint                      u_TexCoordsHandle;
    GLProgram*                GLProgram__;

    RectScreen*                 RectScreen_;
    float*                      imageSize_;

    Texture2D*  texture2D_;
};
