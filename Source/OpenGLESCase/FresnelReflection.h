//
// Created by liuqian8 on 2019/6/27.
//
#pragma once
#include "File.h"
#include "Context.h"
#include "CaseShaderProgram.h"
#include "Sphere.h"
#include "Texture2D.h"
#include "Image.h"
#include "mat4x4.hpp"
class FresnelReflection
{
public:
    FresnelReflection();

    ~FresnelReflection();

    void createScence(Context* context,int width,int height);

    void drawScence(Context* context);

    void move();
private:
    File* file_;

    CaseShaderProgram* caseShaderProgram_;

    Sphere* sphere_;

    Texture2D* texture2D_;

    unsigned vAo_;

    unsigned vBo_;

    glm::vec3 lightPos_;
    glm::vec3 eyePos_;

    glm::mat4 model_;
    glm::mat4 eyeMat_;
    glm::mat4 projectMat_;
    glm::mat4 vpMat4_;

    int count;
};
