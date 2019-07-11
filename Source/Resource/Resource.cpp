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

bool Resource::beginLoad(std::string path)
{
    return false;
}


ResourceWithMetadata::ResourceWithMetadata(Context *context):
    Resource(context)
{

}

ResourceWithMetadata::~ResourceWithMetadata()
{

}
