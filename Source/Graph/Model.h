//
// Created by liuqian8 on 2019/7/10.
//
#pragma once
#include "Resource.h"
class IndexBuffer;
class Model:public ResourceWithMetadata
{
    ENGINE_OBJECT(Model,ResourceWithMetadata);
public:
    Model(Context* context);

    virtual ~Model();

    virtual bool beginLoad(std::string path) override ;

    bool setIndexBuffers(std::vector<IndexBuffer*>& buffers);
};
