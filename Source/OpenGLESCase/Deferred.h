//
// Created by liuqian8 on 2019/5/6.
//
#pragma once

#include "Context.h"
#include "Common.h"
#include "ObjModel.h"
#include "Rect2D.h"

class Deferred
{
public:
    Deferred();
    ~Deferred();

    void createDeferred(Context* context,int width,int height);

    void deferredFirst();

    void move();

protected:

    GLuint                      deferred_fbo_;
    GLuint                      g_position_texture_;
    GLuint                      g_normal_texture_;
    GLuint                      g_color_texture_;
    GLuint                      g_texcoord_texture_;
    GLuint                      g_depth_texture_;


    GLenum                      drawBuffers[3];

    ObjModel*                   objModel;
    Rect2D*                     rect2D;
    Context*                    context_;

    int                         g_texture_buffer_[5];
};
