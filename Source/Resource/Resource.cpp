//
// Created by liuqian8 on 2019/6/19.
//
#include "Resource.h"

Resource::Resource(Context *context):
    Object(context)
{
}

Resource::~Resource()
{
}

bool Resource::loadFile(const string filePath)
{
    name_ = filePath;
    return true;
}
