//
// Created by liuqian8 on 2019/6/14.
//
#pragma once
#include "GPUObject.h"
#include "Object.h"

class Texture: public Object ,public GPUObject
{
    ENGINE_OBJECT(Texture,Object);
public:
    Texture(Context* context);

    virtual ~Texture();

protected:
    virtual bool create()
    {
        return true;
    }

};
