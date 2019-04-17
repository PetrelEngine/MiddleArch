//
// Created by liuqian8 on 2019/4/16.
//
#include "Context.h"
Context::Context()
{
    tempId_ = 0;
}

Context::~Context()

{
    textureList_.clear();
}


void Context::setTextureId(string nameType, int textureId)
{
    if(nameType.size() == 0)
        return;
    textureList_[nameType] = textureId;
}

int Context::getTextureId(string name)
{
    SN_HashMap<string ,int >::const_iterator i = textureList_.find(name);
    if(i!=textureList_.end())
        return i->second;
    else
        return -1;
}