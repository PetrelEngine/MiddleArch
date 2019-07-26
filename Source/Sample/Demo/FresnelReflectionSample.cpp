//
// Created by liuqian8 on 2019/6/28.
//
#include "FresnelReflectionSample.h"

FresnelReflectionSample::FresnelReflectionSample():
        fresnelReflection_(NULL)
{

}

FresnelReflectionSample::~FresnelReflectionSample()
{
    if(fresnelReflection_)
    {
        delete fresnelReflection_;
        fresnelReflection_ = NULL;
    }
}

void FresnelReflectionSample::CreateScence(Context *context, int width, int height)
{
    fresnelReflection_ = new FresnelReflection();
    fresnelReflection_->createScence(context,width,height);
}

void FresnelReflectionSample::RenderOneFrame(Context *context)
{
    fresnelReflection_->drawScence(context);
}

void FresnelReflectionSample::Move()
{
    fresnelReflection_->move();
}
