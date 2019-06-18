//
// Created by liuqian8 on 2019/5/13.
//
#include "ProductNormalMapSample.h"

ProductNormalMapSample::ProductNormalMapSample():
        productNormalTexture_(NULL)
{

}

ProductNormalMapSample::~ProductNormalMapSample()
{
    if(productNormalTexture_)
    {
        delete productNormalTexture_;
        productNormalTexture_ = NULL;
    }
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
