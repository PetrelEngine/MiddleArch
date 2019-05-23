//
// Created by liuqian8 on 2019/5/23.
//
#include "Graphics.h"

Graphics::Graphics(Context* context):
Object(context)
{

}

Graphics::~Graphics()
{

}

void Graphics::SetVBO(unsigned object)
{
    if(object)
        glBindBuffer(GL_ARRAY_BUFFER,object);
}

void Graphics::DrawElements()
{

}

void Graphics::DrawArrays()
{

}
