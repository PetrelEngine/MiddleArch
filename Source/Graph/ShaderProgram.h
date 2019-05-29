//
// Created by liuqian8 on 2019/5/29.
//
#pragma once
#include "GPUObject.h"
#include "Graphics.h"

class ShaderProgram:public GPUObject
{
public:
    ShaderProgram(Graphics* graphics, ShaderVariation* vertexShader, ShaderVariation* pixelShader);

    virtual ~ShaderProgram();

    bool Link();

    ShaderVariation* GetVertexShader() const;

    ShaderVariation* GetPixelShader() const;
protected:
    ShaderVariation* vertexShader_;
    ShaderVariation* pixeShader_;
    SN_HashMap<string,ShaderParameter> shaderParameters_;
    SN_HashMap<pair<char,string>,unsigned > vertexAttributes_;
};
