//
// Created by liuqian8 on 2019/4/16.
//
#include "Context.h"
#include "Object.h"
#include "Common.h"
#include <vector>
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