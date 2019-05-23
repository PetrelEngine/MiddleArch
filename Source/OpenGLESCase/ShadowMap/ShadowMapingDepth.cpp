//
// Created by liuqian8 on 2019/5/23.
//
#include "ShadowMapingDepth.h"
ShadowMapingDepth::ShadowMapingDepth()
{

}

ShadowMapingDepth::~ShadowMapingDepth()
{
    if(File_)
    {
        delete File_;
        File_ = NULL;
    }

}

void ShadowMapingDepth::CreateScence(Context *context, int width, int height)
{

}

void ShadowMapingDepth::RenderScence()
{

}

void ShadowMapingDepth::Move()
{

}

void ShadowMapingDepth::RenderCube()
{

}

void ShadowMapingDepth::RenderPlane()
{

}
