//
// Created by liuqian8 on 2019/5/13.
//
#include "ProductNormalMapSample.h"

ProductNormalMapSample::ProductNormalMapSample()
{

}

ProductNormalMapSample::~ProductNormalMapSample()
{

}

void ProductNormalMapSample::Move()
{

}

void ProductNormalMapSample::CreateScence(Context *context, int width, int height)
{
    productNormalTexture_ = new ProductNoramlTexture();
    productNormalTexture_->CreateScence(context,width,height);
}

void ProductNormalMapSample::RenderOneFrame(Context *context)
{
    productNormalTexture_->Renderer();
}
