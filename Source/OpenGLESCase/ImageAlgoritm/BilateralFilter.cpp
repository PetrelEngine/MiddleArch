//
// Created by liuqian8 on 2019/7/3.
//
#include "BilateralFilter.h"
#include "Image.h"
#include "File.h"
#include "vec2.hpp"
BilateralFilter::BilateralFilter():
    caseShaderProgram_(nullptr),
    vao_(0),
    vbo_(0),
    image_(nullptr),
    texture2D_(nullptr)
{

}

BilateralFilter::~BilateralFilter()
{
    if(caseShaderProgram_)
    {
        delete caseShaderProgram_;
        caseShaderProgram_ = nullptr;
    }

    if(image_)
    {
        delete image_;
        image_ = nullptr;
    }
    if(texture2D_)
    {
        delete texture2D_;
        texture2D_ = nullptr;
    }
}

void BilateralFilter::createScence(Context *context, int width, int height)
{

    caseShaderProgram_ = new CaseShaderProgram();
    File* file_ = context->getSubsystem<File>();
    std::string d_vs = file_->getStringFromFileAssets("SkySnowResources/CoreData/Shaders/BilateralFilter_vs.glsl");
    std::string d_fs = file_->getStringFromFileAssets("SkySnowResources/CoreData/Shaders/BilateralFilter_fs.glsl");
    caseShaderProgram_->link(d_vs,d_fs);
    //创建纹理
    texture2D_ = new Texture2D(context);
    image_ = new Image(context);
    image_->loadImage("/sdcard/SkySnowResources/CoreData/Textures/nobeauty.png");
    texture2D_->setData(image_);


    //组件VAO与VBO缓冲
    unsigned ebo_;
    glGenVertexArrays(1,&vao_);
    glGenBuffers(1,&vbo_);
    glGenBuffers(1,&ebo_);
    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER,vbo_);
    glBufferData(GL_ARRAY_BUFFER,rect2D_.dataSize,rect2D_.data,GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,rect2D_.indexSize,rect2D_.index,GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, rect2D_.DataStride, (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, rect2D_.DataStride, (void*)(2 * sizeof(float)));
}

void BilateralFilter::drawScence(Context *context)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);
    glDisable(GL_DEPTH_TEST);

    caseShaderProgram_->use();

    caseShaderProgram_->setParamater("radius",6.0f);
    caseShaderProgram_->setParamater("sigmaSpace",45.0f);
    caseShaderProgram_->setParamater("sigmaColor",55.0f);
    caseShaderProgram_->setParamater("imageSize",glm::vec2(image_->getImageWidth(),image_->getImageHeight()));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture2D_->getGPUObjectName());

    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLE_STRIP,rect2D_.indexCount,GL_UNSIGNED_INT,0);

    glBindTexture(GL_TEXTURE_2D,0);
    glUseProgram(0);

    glEnable(GL_DEPTH_TEST);
}

void BilateralFilter::move()
{

}
