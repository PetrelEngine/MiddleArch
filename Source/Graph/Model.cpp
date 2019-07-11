//
// Created by liuqian8 on 2019/7/10.
//
#include "Model.h"

Model::Model(Context *context) :
    ResourceWithMetadata(context)
{

}

Model::~Model()
{

}

bool Model::beginLoad(std::string path)
{
    return true;
}

bool Model::setIndexBuffers(std::vector<IndexBuffer *> &buffers)
{
    return true;
}
