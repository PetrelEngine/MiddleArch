//
// Created by liuqian8 on 2019/5/21.
//
#include "PBRLightTextureSample.h"

PBRLightTextureSample::PBRLightTextureSample()
{

}

PBRLightTextureSample::~PBRLightTextureSample()
{
    if(PBR_LightingTexture_)
    {
        delete PBR_LightingTexture_;
        PBR_LightingTexture_= NULL;
    }
}

void PBRLightTextureSample::CreateScence(Context *context, int width, int height)
{
    PBR_LightingTexture_ = new PBR_LightingTexture();
    PBR_LightingTexture_->CreateScence(context,width,height);
}

void PBRLightTextureSample::RenderOneFrame(Context *context)
{
    PBR_LightingTexture_->RenderScence();
}

void PBRLightTextureSample::Move()
{
    PBR_LightingTexture_->move();
}
