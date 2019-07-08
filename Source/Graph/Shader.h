//
// Created by liuqian8 on 2019/5/23.
//
#pragma once
#include "Resource.h"
#include "Context.h"
#include "DataStruct.h"
#define DEFAULTSHADER "/sdcard/SkySnowResources/CoreData/Shaders/"
#define DEFAULTASSETSSHADER "SkySnowResources/CoreData/Shaders/"
class ShaderVariation;
class Shader:public Resource
{
    ENGINE_OBJECT(Shader,Resource);
public:
    Shader(Context* context);

    ~Shader();

    bool load(string vsName,string fsName);

    bool loadAssets(string vsName,string fsName);

    const string& GetSourceCode(ShaderType type) const { return type == VS ? vsSourceCode_ : psSourceCode_; }
private:
    std::string vsSourceCode_;
    std::string psSourceCode_;
};
