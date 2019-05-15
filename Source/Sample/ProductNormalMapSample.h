//
// Created by liuqian8 on 2019/5/13.
//
#pragma once

#include "ProductNoramlTexture.h"
#include "Application.h"

class ProductNormalMapSample: public Application
{
public:
    ProductNormalMapSample();

    ~ProductNormalMapSample();

    virtual void Move();

    virtual void CreateScence(Context* context,int width,int height);

    virtual void RenderOneFrame(Context* context);

protected:
    ProductNoramlTexture* productNormalTexture_;
};
