//
// Created by liuqian8 on 2019/6/27.
//
#include "matrix_transform.hpp"
#include "FresnelReflection.h"
#include "ext.hpp"
FresnelReflection::FresnelReflection():
    sphere_(nullptr),
    caseShaderProgram_(nullptr),
    vBo_(0),
    vAo_(0)
{
}

FresnelReflection::~FresnelReflection()
{
    if(sphere_ != nullptr)
    {
        delete sphere_;
        sphere_ = nullptr;
    }

    if(caseShaderProgram_ != nullptr)
    {
        delete caseShaderProgram_;
        caseShaderProgram_ = nullptr;
    }

    glDeleteVertexArrays(1, &vAo_);
    glDeleteBuffers(1, &vBo_);
}

void FresnelReflection::createScence(Context *context,int width,int height)
{
    caseShaderProgram_  = new CaseShaderProgram();///sdcard/
    file_ = context->getSubsystem<File>();
    std::string d_vs = file_->getStringFromFileAssets("SkySnowResources/CoreData/Shaders/FresnelReflection_vs.glsl");
    std::string d_fs = file_->getStringFromFileAssets("SkySnowResources/CoreData/Shaders/FresnelReflection_fs.glsl");
    caseShaderProgram_->link(d_vs,d_fs);

    //球的纹理加载
    texture2D_ = new Texture2D(context);
    Image* image = new Image(context);
    image->loadImage("/sdcard/SkySnowResources/CoreData/Textures/wood.png");
    texture2D_->setData(image);

    sphere_ = new Sphere();
    //创建vao 与vbo与ebo
    glGenVertexArrays(1, &vAo_);

    unsigned int ebo;
    glGenBuffers(1, &vBo_);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vAo_);
    glBindBuffer(GL_ARRAY_BUFFER, vBo_);
    glBufferData(GL_ARRAY_BUFFER, sphere_->getData().size() * sizeof(float), &sphere_->getData()[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphere_->getIndex().size() * sizeof(unsigned int), &sphere_->getIndex()[0], GL_STATIC_DRAW);
    float stride = (3 + 2 + 3) * sizeof(float);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(5 * sizeof(float)));

    //矩阵以及相关的位置初始化
    model_ = glm::mat4(1.0);
    eyeMat_ = glm::mat4(1.0);
    projectMat_ = glm::mat4(1.0);
    vpMat4_ = glm::mat4(1.0);

    eyePos_ = glm::vec3(0,0,3);
    lightPos_ = glm::vec3(3,0,3);

    model_ = glm::translate(glm::vec3(0.0f,-0.5f,0.0f))*glm::rotate(0.0f,glm::vec3(0,1,0))
             *glm::rotate(-SN_PI/2.0f,glm::vec3(1,0,0))*glm::scale(glm::vec3(1.5f,1.5f,1.5f));
    eyeMat_ = glm::lookAt(eyePos_,glm::vec3(0,0,0),glm::vec3(0,1,0));
    projectMat_ = glm::perspective(glm::radians(120.0f), (float)width / (float)height, 0.1f, 100.0f);
    vpMat4_ = projectMat_ * eyeMat_;
}

void FresnelReflection::drawScence(Context *context)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
    caseShaderProgram_->use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture2D_->getGPUObjectName());

    caseShaderProgram_->setParamater("model",model_);
    caseShaderProgram_->setParamater("vpMat",vpMat4_);
    caseShaderProgram_->setParamater("lightPosition",lightPos_);
    caseShaderProgram_->setParamater("eyePosition",eyePos_);

    glBindVertexArray(vAo_);
    glDrawElements(GL_TRIANGLE_STRIP,sphere_->getIndexCount(),GL_UNSIGNED_INT,0);

    glBindTexture(GL_TEXTURE_2D,0);
    glUseProgram(0);
    glDisable(GL_DEPTH_TEST);
}

void FresnelReflection::move()
{
    //计算相机的z轴的位置
    eyePos_ = glm::vec3(3 * cosf(count * (SN_PI/100)),0,3 * sinf(count * (SN_PI/100)));
    eyeMat_ = glm::lookAt(eyePos_,glm::vec3(0,0,0),glm::vec3(0,1,0));
    vpMat4_ = projectMat_ * eyeMat_;
    count ++;
    count = count % 360;
}