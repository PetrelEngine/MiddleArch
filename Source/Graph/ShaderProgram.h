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

    const ShaderParameter* GetParameter(string param) const;

    const SN_Map<pair<char,string>, unsigned>& GetVertexAttributes() const { return vertexAttributes_; }
protected:
    ShaderVariation* vertexShader_;
    ShaderVariation* pixeShader_;
    SN_Map<string,ShaderParameter> shaderParameters_;
    SN_Map<pair<char,string>,unsigned> vertexAttributes_;
};
