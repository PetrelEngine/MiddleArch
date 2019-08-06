//
// Created by liuqian8 on 2019/4/16.
//
#include "Context.h"
#include "Object.h"
#include "Common.h"

#include "File.h"
#include "Graphics.h"
Context::~Context()

{
    SN_HashMap<string ,Object*>::iterator iter = subsystem_.begin();
    for(;iter != subsystem_.end();iter ++)
    {
        delete iter->second;
    }
    subsystem_.clear();
}

Object* Context::createObject(std::string type)
{
    SN_HashMap<std::string,ObjectFactory*>::const_iterator i = factories_.find(type);
    if(i != factories_.end())
        return i->second->createObject();
    else
        return nullptr;
}

void Context::registerFactory(ObjectFactory* factory)
{
    if (!factory)
        return;

    factories_[factory->getType()] = factory;
}

void Context::registerFactory(ObjectFactory* factory, const char* category)
{
    if (!factory)
        return;

    registerFactory(factory);
    if (string(category).length())
        objectCategories_[category].push_back(factory->getType());
}

void Context::registerSubsystem(Object* subsystem)
{
    if(!subsystem)
        return;
    subsystem_[subsystem->getType()] = subsystem;
}

Object* Context::getSubsystem(string type) const
{
    SN_HashMap<string,Object*>::const_iterator i = subsystem_.find(type);
    if(i != subsystem_.end())
        return i ->second;
    else
        return 0;
}

void Context::removeSubsystem(string ObjectType)
{
    SN_HashMap<string , Object*>::iterator i = subsystem_.find(ObjectType);
    if(i != subsystem_.end())
        subsystem_.erase(i);
}