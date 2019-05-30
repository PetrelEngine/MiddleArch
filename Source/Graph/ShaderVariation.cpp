//
// Created by liuqian8 on 2019/5/29.
//
#include "ShaderVariation.h"
#include "Shader.h"
#include "Graphics.h"
const char* ShaderVariation::elementSemanticNames[] =
{
        "Pos",
        "Normal",
        "BinNormal",
        "Tangetnt",//TANGENT
        "TexCoord",//TEXCOORD
        "Color",//COLOR
        "BlendWeight",//BLENDWEIGHT
        "BlendIndices",//BLENDINDICES
        "ObjectIndex"//OBJECTINDEX
};
ShaderVariation::ShaderVariation(Shader *shader, ShaderType type):
        GPUObject(shader->getSubsystem<Graphics>()),
        owner_(shader),
        type_(type)
{
}

ShaderVariation::~ShaderVariation()
{

}

bool ShaderVariation::Create()
{
    if(!owner_)
        return false;

    object_.name_ = glCreateShader(type_ == VS?GL_VERTEX_SHADER:GL_FRAGMENT_SHADER);
    if(!object_.name_)
        return false;

    const string& originalShaderCode = owner_->GetSourceCode(type_);
    const char* shaderCStr = originalShaderCode.c_str();

    glShaderSource(object_.name_,1,&shaderCStr, nullptr);

    glCompileShader(object_.name_);

    int compiled,length;
    glGetShaderiv(object_.name_,GL_COMPILE_STATUS,&compiled);
    if(!compiled)
    {
        glGetShaderiv(object_.name_, GL_INFO_LOG_LENGTH, &length);
        char* buf = (char*) malloc(length);
        int outLength;
        glGetShaderInfoLog(object_.name_, length, &outLength, buf);
        LOGE("CreateShader Error:%s",buf);
        free(buf);
        glDeleteShader(object_.name_);
        object_.name_ = 0;

    }else{
        LOGI("CreateShader Successful。");
    }
    return true;
}

void ShaderVariation::SetName(const std::string &name)
{
    name_ = name;
}

Shader* ShaderVariation::GetShader() const
{
    return owner_;
}


