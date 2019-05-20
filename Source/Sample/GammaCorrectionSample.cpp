//
// Created by liuqian8 on 2019/5/20.
//
#include "GammaCorrectionSample.h"

GammaCorrectionSample::GammaCorrectionSample()
{

}

GammaCorrectionSample::~GammaCorrectionSample()
{
    if(GammaCorrection_)
    {
        delete GammaCorrection_;
        GammaCorrection_ = NULL;
    }
}

void GammaCorrectionSample::CreateScence(Context *context, int width, int height)
{
    GammaCorrection_ = new GammaCorrection();
    GammaCorrection_->CreateScence(context,width,height);
}

void GammaCorrectionSample::RenderOneFrame(Context *context)
{
    GammaCorrection_->RenderFrame();
}

void GammaCorrectionSample::Move()
{
    GammaCorrection_->Move();
}
