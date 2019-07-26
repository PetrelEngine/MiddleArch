//
// Created by liuqian8 on 2019/7/26.
//
#pragma once
#include "Object.h"

class Resource;

class ResourceCache:public Object
{
    ENGINE_OBJECT(ResourceCache,Object);
public:
    ResourceCache(Context* context);

    virtual ~ResourceCache();

    Resource* getResource(std::string type, const std::string& name, bool sendEventOnFailure = true);

    template <class T> T* getResource(const std::string& name, bool sendEventOnFailure = true);
};

template <class T> T* ResourceCache::getResource(const std::string& name, bool sendEventOnFailure)
{
    std::string type = T::GetTypeStatic();
    return static_cast<T*>(getResource(type, name, sendEventOnFailure));
}
