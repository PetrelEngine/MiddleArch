//
// Created by liuqian8 on 2019/7/26.
//
#include "ResourceCache.h"
#include "Resource.h"

ResourceCache::ResourceCache(Context *context):
    Object(context)
{
}

ResourceCache::~ResourceCache()
{

}

Resource* ResourceCache::getResource(std::string type, const std::string &name,
                                     bool sendEventOnFailure)
{
    return nullptr;
}