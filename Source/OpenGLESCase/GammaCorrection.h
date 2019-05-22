//
// Created by liuqian8 on 2019/5/17.
//
#pragma once

#include <glm/vec3.hpp>
#include "File.h"
#include "GLProgram.hpp"
#include "type_mat4x4.hpp"
#include "type_mat.hpp"
#include "Context.h"
#include "RectData.h"

struct GraphGamma
{
    GLuint       positionsHandle;//位置数据
    GLuint       texCoordssHandle;//纹理坐标
    GLuint       normalsHandle;//法线数据
    GLuint       textureHandle;//纹理
    GLuint       lightPosHandle;//光源位置
    GLuint       lightColorHandle;//光源颜色
    GLuint       gammaHandle;//是否gamma矫正
    GLuint       modelMatrixHandle;//模型矩阵
    GLuint       mvpMatrixHandle;//mvp矩阵
    GLuint       eyePosHandle;//相机位置

    glm::mat4    modelMatrix;
    glm::mat4    cameraMatrix;
    glm::mat4    projectMatrix;
    glm::mat4    mvpMatrix;
    glm::vec3    eyePos;
    bool         isGamma;
    int          texture2DId;
    glm::vec3    lightPos[4];
    glm::vec3    lightColor[4];

};


class GammaCorrection
{
public:
    GammaCorrection();
    ~GammaCorrection();

    void CreateScence(Context* context,int width,int height);

    void Move();

    void RenderFrame();

protected:
    Context*                    Context_;
    File*                       File_;
    Rect3D*                     Rect3D_;
    GLProgram*                  GLProgram__;
    GraphGamma                  GraphGamma_;
};
