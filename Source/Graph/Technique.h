//
// Created by liuqian8 on 2019/6/4.
//
#pragma once

#include <vector>
#include "Common.h"
#include "DataStruct.h"

class ShaderVariation;
//材质渲染的通道，可以定义着色器以及渲染状态
class Pass
{
public:
    Pass(const string& passName);

    virtual ~Pass();

    void setBlendMode(BlendMode mode);

    void setCullMode(CullMode mode);

    void setDepthtestMode(CompareMode mode);

    void setAlphaToCoverage(bool enable);

    void setVertexShader(const string& name);

    void setPixlShader(const string& name);

    void releaseShaders();

    BlendMode getBlendMode() const {return blendMode_;}

    CullMode getCullMode() const {return cullMode_;}

    CompareMode getDepteTestMode() const {return depthTestMode_;}

private:
    BlendMode                       blendMode_;
    CullMode                        cullMode_;
    CompareMode                     depthTestMode_;
    bool                            alphaToCoverage_;
    unsigned                        index_;
    std::string                     vertexShaderName_;
    std::string                     pixelShaderName_;
    std::vector<ShaderVariation*>   vertexShaders_;
    std::vector<ShaderVariation*>   pixelShaders_;
    std::string                     name_;
};

