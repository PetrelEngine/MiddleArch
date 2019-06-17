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

bool Texture2D::create()
{
    release();
    return true;
}

void Texture2D::release()
{

}
