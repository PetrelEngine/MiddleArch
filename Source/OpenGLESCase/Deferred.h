//
// Created by liuqian8 on 2019/5/6.
//
#pragma once

#include <Graph/WBGLProgram.hpp>
#include <Mesh/LoadObj.h>
#include "File.h"
#include "type_mat.hpp"
#include "type_mat4x4.hpp"
#include "Context.h"
#include "Common.h"

struct DeferredGpuHandle
{
    GLuint position;
    GLuint texCoord;
    GLuint normal;
    GLuint uMVPMatix;
    GLuint DefaultTexture;
};

struct DeferredMatrix
{
    glm::mat4 ModelMatrix_;
    glm::mat4 CameraMatrix_;
    glm::mat4 ProjectMatrix_;
    glm::mat4 MVPMatrix_;
};

class Deferred
{
public:
    Deferred();
    ~Deferred();

    void createDeferred(Context* context,int width,int height);

    void deferredFirst();

protected:
    Context*                    Context_;
    File*                       File_;

    WBGLProgram*                WBGLProgram_GBuffer_;
    LoadObj*                    loadObj_;
    int                         textureId_;

    GLuint                      gbuffer_framebuffer;
    GLuint                      gbuffer[2];
    GLuint                      depth_buffer;

    DeferredMatrix      deferredMatrix;
    DeferredGpuHandle   deferredGpuHandle;
};
