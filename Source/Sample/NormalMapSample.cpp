//
// Created by liuqian8 on 2019/5/22.
//
#include "NormalMapSample.h"

NormalMapSample::NormalMapSample()
{

}

NormalMapSample::~NormalMapSample()
{
    if(normalMap_)
    {
        delete normalMap_;
        normalMap_ = NULL;
    }
}

void NormalMapSample::CreateScence(Context *context, int width, int height)
{
    normalMap_ = new NormalMap();
    normalMap_->CreateScence(context,width,height);
}

void NormalMapSample::RenderOneFrame(Context *context)
{
    normalMap_->RenderScence();
}

void NormalMapSample::Move()
{
    normalMap_->Move();
}