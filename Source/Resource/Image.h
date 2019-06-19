//
// Created by liuqian8 on 2019/6/19.
//
#pragma once
#include "Context.h"

class Image
{
public:
    Image(Context* context);

    virtual ~Image();

    bool loadImage(const std::string& filePath,int req_com = 0);

    int getImageWidth();

    int getImageHeight();

    int getImageComponents();

protected:
    int width_;
    int height_;
    int components_;
    const unsigned char*  data_;
};
