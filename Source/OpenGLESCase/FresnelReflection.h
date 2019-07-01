//
// Created by liuqian8 on 2019/6/27.
//
#pragma once
#include "File.h"
#include "Context.h"
#include "CaseShaderProgram.h"
#include "Sphere.h"
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
};
