//
// Created by liuqian8 on 2019/6/19.
//
#pragma once
#include "Object.h"

class Resource:public Object
{
    ENGINE_OBJECT(Resource,Object);
public:
    Resource(Context* context);

    virtual ~Resource();

    bool loadFile(const string filePath);

private:
    string name_;
};
