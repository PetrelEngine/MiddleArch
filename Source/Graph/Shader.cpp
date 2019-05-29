//
// Created by liuqian8 on 2019/5/23.
//
#include "Shader.h"
#include "ShaderVariation.h"
Shader::Shader(Context *context):
    Object(context)
{

}

Shader::~Shader()
{

}

void Shader::SetShaderSourceCode(ShaderType type, std::string shaderCode)
{
    if(type == VS)
        vsSourceCode_ = shaderCode;
    else
        psSourceCode_ = shaderCode;
}
