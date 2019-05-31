//
// Created by liuqian8 on 2019/5/29.
//
#pragma once
#include "ShaderProgram.h"
#include "ShaderVariation.h"
#include "Shader.h"
#include "File.h"
#include "Context.h"
#include "Application.h"
#include "Geometry.h"
class HelloTriangleSample: public Application
{
public:
    HelloTriangleSample();
    ~HelloTriangleSample();

    virtual void CreateScence(Context* context,int width,int height);

    virtual void RenderOneFrame(Context* context);

    virtual void Move();

private:
    Context*                    Context_;
    File*                       File_;
    Shader*                     shader_;
    ShaderVariation*            vertexShader_;
    ShaderVariation*            fragmentShader_;

    VertexBuffer*               vertexBuffer_;
    IndexBuffer*                indexBuffer_;
    Geometry*                   geometry_;
    Graphics*                   graphics_;
};
