//
// Created by liuqian8 on 2019/6/14.
//
#pragma once

#include "Texture.h"
class Texture2D:public Texture
{
    ENGINE_OBJECT(Texture2D,Texture);
public:
    Texture2D(Context* context);

    virtual ~Texture2D();

    void release();

protected:
    virtual bool create() override;

private:

};
