//
// Created by liuqian8 on 2019/5/23.
//
#pragma once

#include "File.h"
#include "GLProgram.hpp"
#include "Context.h"
#include "type_mat.hpp"
#include "type_mat4x4.hpp"
#include "vec3.hpp"
#include "Common.h"

struct GraphShadowMap
{
    GLuint       positionsHandle;   //位置数据
    GLuint       texCoordssHandle;  //纹理坐标
    GLuint       normalsHandle;     //法线数据
    GLuint       texture0Handle;    //纹理
    GLuint       texture1Handle;    //纹理
    GLuint       texture2Handle;    //纹理
    GLuint       lightPosHandle;    //光源位置
    GLuint       lightColorHandle;  //光源颜色
    GLuint       modelMatrixHandle; //模型矩阵
    GLuint       mvpMatrixHandle;   //mvp矩阵
    GLuint       eyePosHandle;      //相机位置

    glm::mat4    modelMatrix;
    glm::mat4    cameraMatrix;
    glm::mat4    projectMatrix;
    glm::mat4    mvpMatrix;
    glm::vec3    eyePos;
    bool         isGamma;
    int          texture2D0Id;
    int          texture2D1Id;
    int          texture2D2Id;
    glm::vec3    lightPos;
    glm::vec3    lightColor;
};
class ShadowMapingDepth
{
public:
    ShadowMapingDepth();

    ~ShadowMapingDepth();

    void CreateScence(Context* context,int width,int height);

    void RenderScence();

    void Move();

private:
    void RenderCube();

    void RenderPlane();

protected:
    Context*                    context_;
    File*                       File_;

    int                         planeVAO;
    GraphShadowMap              GraphShadowMapPlan;
    GLProgram*                  GLProgramPlane_;

    int                         cubeVAO;
    int                         cubeVBO;
    GraphShadowMap              GraphShadowMapCube;
    GLProgram*                  GLProgramCube_;

};
