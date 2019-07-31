//
// Created by liuqian8 on 2019/6/19.
//
#include "Resource.h"
#include "File.h"
Resource::Resource(Context *context):
    Object(context)
{
}

Resource::~Resource()
{
}

bool Resource::beginLoad(Deserializer* source)
{
    return false;
}

bool Resource::load(Deserializer* source)
{
    File* file = context_->getSubsystem<File>();
    string data = file->getStringFromFileAssets("SkySnowResources/CoreData/RenderPaths/Forward.xml");
    LOGE("XML data:%s",data.c_str());
    bool success = beginLoad(source);
    return false;
}

ResourceWithMetadata::ResourceWithMetadata(Context *context):
    Resource(context)
{

}

ResourceWithMetadata::~ResourceWithMetadata()
{

}
