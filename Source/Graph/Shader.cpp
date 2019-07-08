//
// Created by liuqian8 on 2019/5/23.
//
#include "Shader.h"
#include "ShaderVariation.h"
#include "File.h"
Shader::Shader(Context *context):
    Resource(context),
    vsSourceCode_(""),
    psSourceCode_("")
{
}

Shader::~Shader()
{
    vsSourceCode_ = "";
    psSourceCode_ = "";
}

bool Shader::load(string vsName,string fsName)
{
    string vsPasth = DEFAULTSHADER + vsName;
    string fsPasth = DEFAULTSHADER + fsName;
    File* file = context_->getSubsystem<File>();
    bool vsflag,fsflag;
    vsSourceCode_ = file->getStringFromFile(vsPasth);
    if(vsSourceCode_.empty())
        vsflag = false;
    else
        vsflag = true;
    psSourceCode_ = file->getStringFromFile(fsPasth);
    if(psSourceCode_.empty())
        fsflag = false;
    else
        fsflag = true;
    return vsflag && fsflag;
}

bool Shader::loadAssets(string vsName, string fsName)
{
    string vsPasth = DEFAULTASSETSSHADER + vsName;
    string fsPasth = DEFAULTASSETSSHADER + fsName;
    File* file = context_->getSubsystem<File>();
    bool vsflag,fsflag;
    vsSourceCode_ = file->getStringFromFileAssets(vsPasth);
    if(vsSourceCode_.empty())
        vsflag = false;
    else
        vsflag = true;
    psSourceCode_ = file->getStringFromFileAssets(fsPasth);
    if(psSourceCode_.empty())
        fsflag = false;
    else
        fsflag = true;
    return vsflag && fsflag;
}
