//
// Created by liuqian8 on 2019/5/20.
//
#include "StencilTestingSample.h"

StencilTestingSample::StencilTestingSample()
{
}

StencilTestingSample::~StencilTestingSample()
{
    if(StencilTesting_)
    {
        delete StencilTesting_;
        StencilTesting_ = NULL;
    }
}

void StencilTestingSample::CreateScence(Context *context, int width, int height)
{
    StencilTesting_ = new StencilTesting();
    StencilTesting_->CreateScence(context,width,height);
}

void StencilTestingSample::RenderOneFrame(Context *context)
{
    StencilTesting_->RenderScence();
}

void StencilTestingSample::Move()
{

}