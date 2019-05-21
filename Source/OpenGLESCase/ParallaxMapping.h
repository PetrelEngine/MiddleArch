//
// Created by liuqian8 on 2019/5/14.
//
#pragma once

#include "GLProgram.hpp"
#include "type_mat4x4.hpp"
#include "type_mat.hpp"
#include "File.h"
#include "Context.h"
#include "RectData.h"
struct GraphParallax
{
    GLuint      diffuseMapHandle;
    GLuint      normalMapHandle;
    GLuint      depthMapHandle;
    GLuint      positionHandle;
    GLuint      texcoordsHandle;
    GLuint      tangentHandle;
    GLuint      bitgentHandle;
    GLuint      heightScaleHandle;

    GLuint      modelMatrixHandle;
    GLuint      MVPMatrixHandle;
    GLuint      lightPosHandle;
    GLuint      eyePosHandle;

    int         diffuseMapTextureId;
    int         normalMapTextureId;
    int         depthMapTextureId;

    float       heightScale = 0.2f;

    glm::mat4   modelMatrix_;
    glm::mat4   MVPMatrix_;
    glm::mat4   CameraMatrix_;
    glm::mat4   ProjectMatrix_;
    float*      lightPos;
    float*      eyePos;
};
class ParallaxMapping
{
public:
    ParallaxMapping();
    ~ParallaxMapping();

    void CreateScence(Context* context,int width,int height);

    void CaTangentBitgent();

    void RenderParallaxMapping();

protected:
    Context*                    Context_;
    File*                       File_;
    Rect3D*                     Rect3D_;
    GLProgram*                GLProgram__;
    GraphParallax               GraphParallax_;
};
