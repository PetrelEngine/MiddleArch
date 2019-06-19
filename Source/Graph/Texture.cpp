//
// Created by liuqian8 on 2019/6/14.
//
#include "Texture.h"
#include "Graphics.h"
Texture::Texture(Context* context):
    Resource(context),
    GPUObject(getSubsystem<Graphics>())
{
}

Texture::~Texture()
{

}
