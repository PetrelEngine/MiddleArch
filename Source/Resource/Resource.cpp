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
    bufferData_ = file->getStringFromFileAssets("SkySnowResources/CoreData/RenderPaths/Forward.xml");
    LOGI("XML data:%s",bufferData_.c_str());
    bool success = beginLoad(source);
    return success;
}

ResourceWithMetadata::ResourceWithMetadata(Context *context):
    Resource(context)
{

}

ResourceWithMetadata::~ResourceWithMetadata()
{

}
