//
// Created by liuqian8 on 2019/6/14.
//
#pragma once
#include "Texture.h"
class Image;
class Texture2D:public Texture
{
    ENGINE_OBJECT(Texture2D,Texture);
public:
    Texture2D(Context* context);

    virtual ~Texture2D();

    void release();

    bool setSize(int width,int height, unsigned format,TextureUsage usage = TEXTURE_STATIC,int multiSample = 1,bool autoResolve = true);

    bool setData(unsigned level, int x, int y, int width, int height, const void* data);

    bool setData(Image* image,bool useAlpha = false);

protected:
    virtual bool create() override;

private:

};
