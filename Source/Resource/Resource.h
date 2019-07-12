//
// Created by liuqian8 on 2019/6/19.
//
#pragma once
#include "Object.h"

class Deserializer;

class Resource:public Object
{
    ENGINE_OBJECT(Resource,Object);
public:
    Resource(Context* context);

    virtual ~Resource();

    virtual bool beginLoad(Deserializer& source);
//    bool loadFile(const string filePath);

private:
    string name_;
protected:
//    Image*  image_;
};

class ResourceWithMetadata:public Resource
{
    ENGINE_OBJECT(ResourceWithMetadata,Resource);
public:
    ResourceWithMetadata(Context* context);

    virtual ~ResourceWithMetadata();
};
