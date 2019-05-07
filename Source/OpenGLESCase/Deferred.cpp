//
// Created by liuqian8 on 2019/5/6.
//
#include "transform.hpp"
#include <glm/ext.hpp>
#include <File/File.h>
#include "Deferred.h"

Deferred::Deferred()
{

}

Deferred::~Deferred()
{

}

void Deferred::createDeferred(Context *context, int width, int height)
{
    Context_ = context;
    /** Create Gbuffer*/

    /* Create framebuffer */
    glGenFramebuffers(1, &gbuffer_framebuffer);

    glGenTextures(2, gbuffer);
    for(int i=0;i < 2; i++) {
        glBindTexture(GL_TEXTURE_2D, gbuffer[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    glGenTextures(1, &depth_buffer);
    glBindTexture(GL_TEXTURE_2D, depth_buffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);

    /** GBuffer format
     *  [0] RGB: Albedo
     *  [1] RG: VS Normal (encoded)
     *  [2] R: Depth
     */
    glBindTexture(GL_TEXTURE_2D, gbuffer[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

    glBindTexture(GL_TEXTURE_2D, gbuffer[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, width, height, 0, GL_RG, GL_FLOAT, 0);
    /* Depth texture */
    glBindTexture(GL_TEXTURE_2D, depth_buffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, gbuffer_framebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gbuffer[0], 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gbuffer[1], 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_buffer, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    //延迟渲染的物体的数据
    File_ = new File(Context_);
    std::string vertexShaderSource = File_->getStringFromFileAssets("deferredVertex.glsl");
    std::string fragShaderSource = File_->getStringFromFileAssets("deferredFragment.glsl");
    WBGLProgram_GBuffer_  = new WBGLProgram();
    WBGLProgram_GBuffer_->initWithVertexShaderString(vertexShaderSource,fragShaderSource);
    WBGLProgram_GBuffer_->addAttribute("position");
    WBGLProgram_GBuffer_->addAttribute("texCoord");
    WBGLProgram_GBuffer_->addAttribute("normal");
    WBGLProgram_GBuffer_->link();


    deferredGpuHandle.position = WBGLProgram_GBuffer_->getAttributeIndex("position");
    deferredGpuHandle.texCoord = WBGLProgram_GBuffer_->getAttributeIndex("texCoord");
    deferredGpuHandle.normal = WBGLProgram_GBuffer_->getAttributeIndex("normal");
    deferredGpuHandle.uMVPMatix = WBGLProgram_GBuffer_->getUniformIndex("uMVPMatix");
    deferredGpuHandle.DefaultTexture = WBGLProgram_GBuffer_->getUniformIndex("DefaultTexture");

    loadObj_ = new LoadObj();

    bool loadout = loadObj_->LoadFile("/sdcard/PBRObj/Fish/fish.obj");

    deferredMatrix.MVPMatrix_ = glm::mat4(1.0);
    deferredMatrix.ModelMatrix_ = glm::mat4(1.0);
    deferredMatrix.CameraMatrix_ = glm::mat4(1.0);
    deferredMatrix.ProjectMatrix_ = glm::mat4(1.0);

    float pi = 3.1415926f;

    deferredMatrix.ModelMatrix_ = glm::translate(glm::vec3(0,-1,-5))*glm::rotate(pi/2.f,glm::vec3(0,1,0))* glm::rotate(pi/1.f,glm::vec3(1,0,0))*glm::scale(glm::vec3(0.05,0.05,0.05));
    deferredMatrix.CameraMatrix_ = glm::lookAt(glm::vec3(5,1,-1),glm::vec3(0,-1,-1),glm::vec3(0,1,0));
    deferredMatrix.ProjectMatrix_ = glm::frustumRH(-1,1,-1,1,1,1000);

    deferredMatrix.MVPMatrix_ = deferredMatrix.ProjectMatrix_*deferredMatrix.CameraMatrix_* deferredMatrix.ModelMatrix_;
    textureId_ = context->getTextureId("fish");
}


void Deferred::deferredFirst()
{
    GLenum buffers[] = {
            GL_COLOR_ATTACHMENT0,
            GL_COLOR_ATTACHMENT1,
            GL_COLOR_ATTACHMENT2,
    };

    glBindFramebuffer(GL_FRAMEBUFFER, gbuffer_framebuffer);
    glDrawBuffers(2, buffers);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
    glCullFace(GL_BACK);
    glUseProgram(WBGLProgram_GBuffer_->getProgramId());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId_);
    glUniform1i(deferredGpuHandle.DefaultTexture,0);

    glEnableVertexAttribArray(deferredGpuHandle.position);
    glEnableVertexAttribArray(deferredGpuHandle.normal);
    glEnableVertexAttribArray(deferredGpuHandle.texCoord);

    glVertexAttribPointer(deferredGpuHandle.position, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), loadObj_->LoadedVertices.data());
    glVertexAttribPointer(deferredGpuHandle.normal, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (reinterpret_cast<char*>(loadObj_->LoadedVertices.data()) + 3 * sizeof(GL_FLOAT)));
    glVertexAttribPointer(deferredGpuHandle.texCoord, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (reinterpret_cast<char*>(loadObj_->LoadedVertices.data()) + 6 * sizeof(GL_FLOAT)));

    glUniformMatrix4fv(deferredGpuHandle.uMVPMatix, 1, false, (GLfloat *)&deferredMatrix.MVPMatrix_);
    glDrawElements(GL_TRIANGLES, loadObj_->LoadedIndices.size(),GL_UNSIGNED_INT,loadObj_->LoadedIndices.data());

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
    glCullFace(GL_BACK);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

