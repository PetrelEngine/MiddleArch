//
// Created by liuqian8 on 2019/5/6.
//
#include <File/File.h>
#include "Deferred.h"

Deferred::Deferred()
{

}

Deferred::~Deferred()
{
    if(objModel)
    {
        delete objModel;
        objModel = NULL;
    }

    if(rect2D)
    {
        delete rect2D;
        rect2D = NULL;
    }
}

void Deferred::createDeferred(Context *context, int width, int height)
{
    context_ = context;
    //创建fbo
    glGenFramebuffers(1,&deferred_fbo_);
    //绑定fbo
    glBindFramebuffer(GL_FRAMEBUFFER,deferred_fbo_);
    //创建几何buffer的纹理
    glGenTextures(1, &g_position_texture_);//位置数据纹理
    glGenTextures(1, &g_normal_texture_);//法线数据纹理
    glGenTextures(1, &g_color_texture_);//颜色数据纹理
    glGenTextures(1, &g_texcoord_texture_);//纹理坐标数据纹理
    glGenTextures(1, &g_depth_texture_);//深度数据纹理

    //position
    glBindTexture(GL_TEXTURE_2D, g_position_texture_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //Normal
    glBindTexture(GL_TEXTURE_2D, g_normal_texture_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //Color
    glBindTexture(GL_TEXTURE_2D, g_color_texture_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //texcoord
    glBindTexture(GL_TEXTURE_2D, g_texcoord_texture_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //Create depth texture
    glBindTexture(GL_TEXTURE_2D, g_depth_texture_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);

    //Attach textures to FBO
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, g_position_texture_, 0);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, g_normal_texture_, 0);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, g_color_texture_, 0);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, g_texcoord_texture_, 0);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, g_depth_texture_, 0);

    drawBuffers[0] = GL_COLOR_ATTACHMENT0;
    drawBuffers[1] = GL_COLOR_ATTACHMENT1;
    drawBuffers[2] = GL_COLOR_ATTACHMENT2;
    drawBuffers[3] = GL_COLOR_ATTACHMENT3;
    glDrawBuffers(4, drawBuffers);
    //Unbind
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    g_texture_buffer_[0] = g_position_texture_;
    g_texture_buffer_[1] = g_normal_texture_;
    g_texture_buffer_[2] = g_color_texture_;
    g_texture_buffer_[3] = g_depth_texture_;
    g_texture_buffer_[4] = g_texcoord_texture_;


    objModel = new ObjModel();
    objModel->CreateObj(context,width,height);

    rect2D = new Rect2D();
    rect2D->CreateRect2D(context,width,height);
}


void Deferred::move()
{
    objModel->move();
}

int isp = false;
void Deferred::deferredFirst()
{

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, deferred_fbo_);
    glDrawBuffers ( 4, drawBuffers );
    glDepthMask(GL_TRUE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    objModel->drawObj(context_);

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glDepthMask(GL_FALSE);
    glDisable(GL_DEPTH_TEST);
    if(!isp)
    {
        LOGI("gbuffer[0]:%d",g_texture_buffer_[0]);
        LOGI("gbuffer[1]:%d",g_texture_buffer_[1]);
        LOGI("gbuffer[2]:%d",g_texture_buffer_[2]);
        LOGI("gbuffer[3]:%d",g_texture_buffer_[3]);
        isp = true;
    }

    glDisable(GL_DEPTH_TEST);
    rect2D->DrawRect2D(context_,g_texture_buffer_);
}

