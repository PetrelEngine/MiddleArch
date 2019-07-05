//
// Created by liuqian8 on 2019/7/3.
//
#pragma once
#include "RectData.h"
#include "Context.h"
#include "CaseShaderProgram.h"
#include "Texture2D.h"
#include "Image.h"
//双边滤波处理
class BilateralFilter
{
public:
    BilateralFilter();
    ~BilateralFilter();

    void createScence(Context* context,int width,int height);

    void drawScence(Context* context);

    void move();

protected:
    CaseShaderProgram* caseShaderProgram_;

    RectScreen rect2D_;
    Texture2D* texture2D_;
    Image* image_;

    unsigned vao_;
    unsigned vbo_;
};
