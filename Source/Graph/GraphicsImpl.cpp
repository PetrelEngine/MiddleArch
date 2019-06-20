//
// Created by liuqian8 on 2019/5/29.
//
#include "GraphicsImpl.h"

GraphicsImpl::GraphicsImpl():
        vertexBuffersDirty_(false),
        shaderProgram_(nullptr),
        activeTexture_(0)
{

}

GraphicsImpl::~GraphicsImpl()
{

}