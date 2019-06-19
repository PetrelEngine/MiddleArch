//
// Created by liuqian8 on 2019/6/19.
//
#include "Resource.h"

Resource::Resource(Context *context):
    Object(context),
    image_(NULL)
{
}

Resource::~Resource()
{
    if(image_)
    {
        delete image_;
        image_ = NULL;
    }
}

bool Resource::loadFile(const string filePath)
{
    name_ = filePath;
    if(image_ == NULL)
        image_ = new Image(context_);
    image_->loadImage(filePath);
    return true;
}
