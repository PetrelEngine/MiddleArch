//
// Created by liuqian8 on 2019/5/15.
//
#include "ParallaxMappingSample.h"

ParallaxMappingSample::ParallaxMappingSample()
{

}

ParallaxMappingSample::~ParallaxMappingSample()
{

}

void ParallaxMappingSample::CreateScence(Context *context, int width, int height)
{
    ParallaxMapping_ = new ParallaxMapping();
    ParallaxMapping_ ->CreateScence(context,width,height);
}

void ParallaxMappingSample::RenderOneFrame(Context *context)
{
    ParallaxMapping_->RenderParallaxMapping();
}

void ParallaxMappingSample::Move()
{

}