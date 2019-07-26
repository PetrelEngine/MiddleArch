//
// Created by liuqian8 on 2019/7/4.
//
#include "BilateralFilterSample.h"

BilateralFilterSample::BilateralFilterSample():
        bilateralFilter_(nullptr)
{

}

BilateralFilterSample::~BilateralFilterSample()
{
    if(bilateralFilter_)
    {
        delete bilateralFilter_;
        bilateralFilter_ = nullptr;
    }
}

void BilateralFilterSample::CreateScence(Context *context, int width, int height)
{
    bilateralFilter_ = new BilateralFilter();
    bilateralFilter_->createScence(context,width,height);
}

void BilateralFilterSample::RenderOneFrame(Context *context)
{
    bilateralFilter_->drawScence(context);
}

void BilateralFilterSample::Move()
{
    bilateralFilter_->move();
}
