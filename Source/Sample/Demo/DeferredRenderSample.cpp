//
// Created by liuqian8 on 2019/5/6.
//
#include "DeferredRenderSample.h"

DeferredRenderSample::DeferredRenderSample():
        Deferred_(NULL)
{

}

DeferredRenderSample::~DeferredRenderSample()
{
    if(Deferred_ != NULL)
    {
        delete Deferred_;
        Deferred_ = NULL;
    }
}

void DeferredRenderSample::Move()
{
    Deferred_->move();
}

void DeferredRenderSample::CreateScence(Context *context, int width, int height)
{
    Deferred_ = new Deferred();
    Deferred_->createDeferred(context,width,height);
}

void DeferredRenderSample::RenderOneFrame(Context *context)
{
    Deferred_->deferredFirst();
}
