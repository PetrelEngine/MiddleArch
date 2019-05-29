//
// Created by liuqian8 on 2019/5/23.
//

#pragma once

#include "Context.h"
#include "DataStruct.h"

class ShaderVariation;
class Shader:public Object
{
    ENGINE_OBJECT(Shader,Object);
public:
    Shader(Context* context);

    ~Shader();

    void SetShaderSourceCode(ShaderType type,std::string shaderCode);

    const string& GetSourceCode(ShaderType type) const { return type == VS ? vsSourceCode_ : psSourceCode_; }
private:
    std::string vsSourceCode_;
    std::string psSourceCode_;
};
