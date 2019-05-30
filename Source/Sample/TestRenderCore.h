//
// Created by liuqian8 on 2019/5/29.
//

#pragma once

#include "ShaderProgram.h"
#include "ShaderVariation.h"
#include "Shader.h"
#include "File.h"
#include "Context.h"

class TestRenderCore
{
public:
    TestRenderCore();
    ~TestRenderCore();

    void testShader(Context* context);

private:
    Context*                    Context_;
    File*                       File_;
    Shader*                     shader_;
    ShaderVariation*            vertexShader_;
    ShaderVariation*            fragmentShader_;

};
