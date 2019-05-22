//
// Created by liuqian8 on 2019/5/22.
//
#pragma once

#include "type_mat.hpp"
#include "vec3.hpp"
#include "type_mat4x4.hpp"
#include "GLProgram.hpp"
#include "File.h"
#include "Context.h"
#include "RectData.h"

struct GraphNormal
{
    GLuint          positionHandle;
    GLuint          normalHandle;
    GLuint          texcoordsHandle;
    GLuint          lightPositionHandle;
    GLuint          lightColorHandle;
    GLuint          eyePositionHandle;
    GLuint          modelMatrixHandle;
    GLuint          mvpMatrixHandle;
    GLuint          normalMapHandle;
    GLuint          colorMapHandle;
    GLuint          normalScalehandle;


    glm::mat4       modelMatrix;
    glm::mat4       cameraMatrix;
    glm::mat4       projectMatrix;
    glm::mat4       mvpMatrix;
    glm::vec3       eyePos;
    int             texture2DId;
    int             normal2DId;
    float           normalScale = 10.0f;
    glm::vec3       lightPos;
    glm::vec3       lightColor;
};

class NormalMap
{
public:
    NormalMap();

    ~NormalMap();

    void CreateScence(Context* context,int width,int height);

    void RenderScence();

    void Move();
protected:
    Context*                    Context_;
    File*                       File_;
    GLProgram*                  GLProgram__;
    GraphNormal                 GraphNormal_;
    Rect3D                      Rect3D_;
};
