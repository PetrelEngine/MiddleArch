//
// Created by liuqian8 on 2019/6/5.
//
#include "Technique.h"

Pass::Pass(const string &passName):
    blendMode_(BLEND_REPLACE),
    cullMode_(MAX_CULLMODES),
    depthTestMode_(CMP_LESSEQUAL),
    alphaToCoverage_(false)
{

}

Pass::~Pass()
{

}

void Pass::setBlendMode(BlendMode mode)
{
    blendMode_ = mode;
}

void Pass::setCullMode(CullMode mode)
{
    cullMode_ = mode;
}

void Pass::setDepthtestMode(CompareMode mode)
{
    depthTestMode_ = mode;
}

void Pass::setAlphaToCoverage(bool enable)
{
    alphaToCoverage_ = enable;
}

void Pass::setVertexShader(const string &name)
{
    vertexShaderName_ = name;
}

void Pass::setPixlShader(const string &name)
{
    pixelShaderName_ = name;
}

void Pass::releaseShaders()
{
    vertexShaders_.clear();
    pixelShaders_.clear();
}

