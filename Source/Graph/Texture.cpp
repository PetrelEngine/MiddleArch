//
// Created by liuqian8 on 2019/6/14.
//
#include "Texture.h"

Texture::Texture(Context* context):
    Object(context),
    GPUObject(getSubsystem<Graphics>())
{
}

Texture::~Texture()
{

}