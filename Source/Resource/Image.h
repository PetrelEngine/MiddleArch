//
// Created by liuqian8 on 2019/6/19.
//
#pragma once
#include "Context.h"
#include "Resource.h"
class Image:public Resource
{
    ENGINE_OBJECT(Image,Resource)
public:
    Image(Context* context);

    virtual ~Image();

    bool loadImage(const std::string& filePath,int req_com = 0);

    int getImageWidth();

    int getImageHeight();

    int getImageComponents();

    unsigned char* getData();

protected:
    int width_;
    int height_;
    int components_;
    unsigned char*  data_;
};
