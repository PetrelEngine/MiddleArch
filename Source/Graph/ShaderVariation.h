//
// Created by liuqian8 on 2019/5/23.
//
#pragma once
#include "GPUObject.h"
#include "DataStruct.h"
class Shader;

struct ShaderParameter
{
    ShaderParameter()
    {
    }
    ShaderType type_;
    std::string name_;
    int location_;
    unsigned glType_;
};
class ShaderVariation: public GPUObject
{
public:
    ShaderVariation(Shader* shader,ShaderType type);

    virtual ~ShaderVariation();

    void SetName(const std::string& name);

    bool Create();

    ShaderType GetShaderType()const {return type_;}

    Shader* GetShader() const;

    const string& GetName() const { return name_; }

    static const char* elementSemanticNames[];
private:
    ShaderType type_;

    std::string name_;

    Shader* owner_;
};
