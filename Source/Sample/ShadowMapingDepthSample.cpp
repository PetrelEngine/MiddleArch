//
// Created by liuqian8 on 2019/6/26.
//
#include "ShadowMapingDepthSample.h"

ShadowMapingDepthSample::ShadowMapingDepthSample():
        shadowMapingDepth_(NULL)
{

}

ShadowMapingDepthSample::~ShadowMapingDepthSample()
{
    if(shadowMapingDepth_ != NULL)
    {
        delete shadowMapingDepth_;
        shadowMapingDepth_ = NULL;
    }
}

void ShadowMapingDepthSample::CreateScence(Context *context, int width, int height)
{
    shadowMapingDepth_ = new ShadowMapingDepth();
    shadowMapingDepth_->CreateScence(context,width,height);
}

void ShadowMapingDepthSample::RenderOneFrame(Context *context)
{
    shadowMapingDepth_->RenderScence();
}

void ShadowMapingDepthSample::Move()
{
    shadowMapingDepth_->Move();
}

