//
// Created by liuqian8 on 2019/6/14.
//
#include "Texture2D.h"

Texture2D::Texture2D(Context* context):
    Texture(context)
{

}

Texture2D::~Texture2D()
{

}

bool Texture2D::createTexture2D(const string filePath)
{
    bool flag = loadFile(filePath);
    width_ = image_->getImageWidth();
    height_ = image_->getImageHeight();
    create();
    return flag;
}

bool Texture2D::create()
{
    release();
    if(!graphics_ || !width_ || !height_)
    {
        LOGE("No texture created, can not get data");
        return false;
    }

    glGenTextures(1,&object_.name_);
    if(usage_ == TEXTURE_DEPTHSTENCIL)
    {
        requestedLevels_ = 1;
    }else if(usage_ == TEXTURE_RENDERTARGET)
    {
        if(requestedLevels_ != 1)
        {
            regenerateLevels();
            requestedLevels_ = 0;
        }
    }

    updateParameters();

    return true;
}

void Texture2D::release()
{

}
