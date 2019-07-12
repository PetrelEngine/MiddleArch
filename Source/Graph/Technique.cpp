//
// Created by liuqian8 on 2019/6/5.
//
#include "Technique.h"

Pass::Pass(const string &passName):
    blendMode_(BLEND_REPLACE),
    cullMode_(MAX_CULLMODES),
    depthTestMode_(CMP_LESSEQUAL),
    alphaToCoverage_(false),
    name_(passName)
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

Technique::Technique(Context *context):
    Resource(context)
{

}

Technique::~Technique()
{

}

bool Technique::beginLoad(Deserializer &source)
{
    return false;
}

Pass* Technique::createPass(const std::string &passName)
{
    Pass* oldPass = getPass(passName);
    if(oldPass)
        return oldPass;
    Pass* newPass = new Pass(passName);
    unsigned passIndex = newPass->getIndex();
    if(passIndex >= passes_.size())
        passes_.resize(passIndex + 1);
    passes_[passIndex] = newPass;
    return newPass;
}

void Technique::removePass(const std::string &passName)
{

}

Pass* Technique::getPass(unsigned passIndex)
{
    return nullptr;
}

Pass* Technique::getPass(const std::string &passName)
{
    return nullptr;
}

std::vector<std::string> Technique::getPassNames() const
{
    std::vector<string> ret;
    for (int i = 0; i < passes_.size();i ++)
    {
        Pass* pass = passes_[i];
        if (pass)
            ret.push_back(pass->getName());
    }
    return ret;
}

std::vector<Pass*> Technique::getPasses() const
{
    std::vector<Pass*> ret;

    for (int i = 0; i < passes_.size();i++)
    {
        Pass* pass = passes_[i];
        if (pass)
            ret.push_back(pass);
    }
    return ret;

}

unsigned Technique::getNumPasses() const
{
    return 0;
}

void Technique::releaseShaders()
{

}

