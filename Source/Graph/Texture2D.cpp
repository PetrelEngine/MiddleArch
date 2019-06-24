//
// Created by liuqian8 on 2019/6/14.
//
#include "Texture2D.h"
#include "Image.h"
#include "Graphics.h"
Texture2D::Texture2D(Context* context):
    Texture(context)
{
    target_ = GL_TEXTURE_2D;
}

Texture2D::~Texture2D()
{
    release();
}

bool Texture2D::setSize(int width, int height, unsigned format, TextureUsage usage, int multiSample,bool autoResolve)
{
    if(width <= 0 || height <= 0)
    {
        LOGE("zero or negative texture dimensions");
        return false;
    }

    if(usage >= TEXTURE_RENDERTARGET)
    {
        addressMode_[COORD_U] = ADDRESS_CLAMP;
        addressMode_[COORD_V] = ADDRESS_CLAMP;
        filterMode_ = FILTER_DEFAULT;
    }
    usage_ = usage;
    width_ = width;
    height_ = height;
    format_ = format;
    depth_ = 1;
    return create();
}

bool Texture2D::setData(unsigned level, int x, int y, int width, int height, const void *data)
{
    if(!object_.name_ ||!graphics_)
    {
        LOGE("no texture created,can not set data.");
        return false;
    }
    if(!data)
    {
        LOGE("null source for seting data.");
        return false;
    }

    if(level > levels_)
    {
        LOGE("illegal mip level for setting data.");
        return false;
    }

    glTexImage2D(target_, level, format_, width, height, 0, getExternalFormat(format_),getDataType(format_), data);
    return true;
}

bool Texture2D::setData(Image *image, bool useAlpha)
{
    if(!image)
    {
        LOGE("Null image, can not set data");
        return false;
    }
    //不考虑图像压缩的问题
    unsigned components = (unsigned)image->getImageComponents();

    unsigned char* levelData = image->getData();

    int levelWidth = image->getImageWidth();

    int levelHeight = image->getImageHeight();

    unsigned format = 0;

    switch (components)
    {
        case 1:
            format = GL_R8;
            break;
        case 2:
            format = GL_RG8;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            break;
    }
    setSize(levelWidth,levelHeight,format);
    if(!object_.name_)
        return false;
    //mipmap的处理操作,目前暂时不使用mipmap操作
    for(int i = 0; i < levels_;i ++)
    {
        setData(i,0,0,levelWidth,levelHeight,levelData);
    }
    return true;
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

    graphics_->setTextureForUpdate(this);

    levels_ = 1;
    updateParameters();

    return true;
}

void Texture2D::release()
{
    if(object_.name_)
    {
        if(!graphics_)
            return;
        for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        {
            if (graphics_->getTexture(i) == this)
                graphics_->setTexture(i, nullptr);
        }
        glDeleteTextures(1, &object_.name_);
        object_.name_ = 0;
    }
    levelsDirty_ = false;
}
