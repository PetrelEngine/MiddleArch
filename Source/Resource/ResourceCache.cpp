//
// Created by liuqian8 on 2019/7/26.
//
#include "ResourceCache.h"
#include "Resource.h"
#include "File.h"
#include "XMLFile.h"
ResourceCache::ResourceCache(Context *context):
    Object(context)
{
    registerResourceLibrary(context_);
}

ResourceCache::~ResourceCache()
{

}

Resource* ResourceCache::getResource(std::string type, const std::string &name,
                                     bool sendEventOnFailure)
{
    LOGI("Resource Cache getResource start.");
    LOGI("Resource name:%s",name.c_str());
    if(name.empty())
        return nullptr;

    Resource* existing = findResource(name);
    if(existing)
        return existing;

    Resource* resource = (Resource*)context_->createObject(type);
    File* file = getSubsystem<File>();
    if(resource == nullptr)
        LOGE("resource is nullptr.");
    if(!resource->load(file))
    {
        LOGE("打印error数据。并应该记录错误日志数据。");
    }

    resourceGroups_[type].resources_[name] = resource;
    //
    //这里应该有内存检测的代码，如果超过某个内存限定，那么清理一些不用资源内存占用
    //
    LOGI("创建Resources成功。");
    return resource;
}

Resource* ResourceCache::findResource(std::string type, string name)
{

    return nullptr;
}

Resource* ResourceCache::findResource(string name)
{
    for(SN_Map<std::string,ResourceGroup>::iterator i = resourceGroups_.begin();i != resourceGroups_.end(); i ++)
    {
        std::string name = i->first;
        SN_Map<std::string,Resource*>::iterator j = i->second.resources_.find(name);
        if(j != i->second.resources_.end())
        {
            return j->second;
        }
    }
    return nullptr;
}

void ResourceCache::registerResourceLibrary(Context *context)
{
    XMLFile::registerObject(context);
}