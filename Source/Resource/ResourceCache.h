//
// Created by liuqian8 on 2019/7/26.
//
#pragma once
#include "Object.h"
#include <vector>
class Resource;

struct ResourceGroup
{
    ResourceGroup():
            memoryBudget_(0),
            memoryUse_(0)
    {
    }

    unsigned long long memoryBudget_;

    unsigned long long memoryUse_;

    SN_Map<std::string,Resource*> resources_;
};

class ResourceCache:public Object
{
    ENGINE_OBJECT(ResourceCache,Object);
public:
    ResourceCache(Context* context);

    virtual ~ResourceCache();

    Resource* getResource(std::string type, const std::string& name, bool sendEventOnFailure = true);

    template <class T> T* getResource(const std::string& name, bool sendEventOnFailure = true);

private:
    Resource* findResource(std::string type,string name);

    Resource* findResource(string name);

    SN_Map<std::string,ResourceGroup> resourceGroups_;

    std::vector<string> resourcesDirs_;
};

template <class T> T* ResourceCache::getResource(const std::string& name, bool sendEventOnFailure)
{
    std::string type = T::GetTypeStatic();
    return static_cast<T*>(getResource(type, name, sendEventOnFailure));
}
