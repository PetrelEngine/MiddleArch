//
// Created by liuqian8 on 2019/7/10.
//
#pragma once
#include "Object.h"
class Serializable:public Object
{
    ENGINE_OBJECT(Serializable,Object);
public:
    Serializable(Context* context);

    virtual ~Serializable();

    virtual bool load(std::string source, bool setInstanceDefault = false);
};
