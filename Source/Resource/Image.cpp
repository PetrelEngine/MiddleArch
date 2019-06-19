//
// Created by liuqian8 on 2019/6/19.
//
#include "Image.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
Image::Image(Context *context):
    width_(0),
    height_(0),
    components_(0),
    data_(NULL)
{
}

Image::~Image()
{

}

bool Image::loadImage(const std::string &filePath, int req_com)
{
    data_ = stbi_load(filePath.c_str(),&width_,&height_,&components_,req_com);

    if(req_com != 0 && components_ >req_com)
        components_ = req_com;
    if(nullptr == data_)
    {
        LOGE("Can't open the file.");
        return false;
    }else{
        LOGI("Load image success.");
        LOGI("image width:%d",width_);
        LOGI("image height:%d",height_);
        LOGI("image components:%d",components_);
        return true;
    }
}

int Image::getImageWidth()
{
    return width_;
}

int Image::getImageHeight()
{
    return height_;
}

int Image::getImageComponents()
{
    return components_;
}