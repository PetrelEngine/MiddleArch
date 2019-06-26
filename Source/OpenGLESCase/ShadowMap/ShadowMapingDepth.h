//
// Created by liuqian8 on 2019/5/23.
//
#pragma once

#include "CubeBox.h"
#include "Plane.h"
#include "File.h"
#include "CaseShaderProgram.h"
#include "Context.h"
#include "type_mat.hpp"
#include "type_mat4x4.hpp"
#include "vec3.hpp"
#include "Common.h"
#include "Texture2D.h"

class ShadowMapingDepth
{
public:
    ShadowMapingDepth();

    ~ShadowMapingDepth();

    void CreateScence(Context* context,int width,int height);

    void RenderScence();

    void Move();

private:
    void initialPlane();

    void RenderMode();

    void RenderCube();

    void RenderQuad();

protected:
    Context*                    context_;
    File*                       file_;

    unsigned                         planeVAO;
    unsigned                         cubeVAO;
    unsigned                         cubeVBO;

    CaseShaderProgram*                  GLProgram_depth_;
    CaseShaderProgram*                  GLProgram_use_depth_;

    Texture2D*                  texture_;

    CubeBox* cubeBox_;

    unsigned depthMapFbo;
    unsigned depthMap = 0;

    int width_;
    int height_;

    glm::mat4 cameraMat_;
    glm::mat4 projectMat_;
    glm::vec3 lightPos;

    glm::mat4 vpMat_;

    unsigned quadVAO;
    unsigned quadVBO;
};
