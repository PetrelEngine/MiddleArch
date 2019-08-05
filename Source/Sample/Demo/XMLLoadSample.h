//
// Created by liuqian8 on 2019/7/31.
//
#pragma once
#include "Application.h"
#include "XMLFile.h"
#include "RenderPath.h"
class XMLLoadSample: public Application
{
public:
    XMLLoadSample();

    virtual ~XMLLoadSample();

    virtual void Move();

    virtual void CreateScence(Context* context,int width,int height);

    virtual void RenderOneFrame(Context* context);

private:
    XMLFile* xmlFile_;
    RenderPath* defaultRenderPath_;
};
