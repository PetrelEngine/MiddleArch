//
// Created by liuqian8 on 2019/5/13.
//
#include "ProductNoramlTexture.h"
#include "Image.h"
ProductNoramlTexture::ProductNoramlTexture():
        GLProgram__(nullptr),
        texture2D_(nullptr),
        RectScreen_(nullptr)
{

}

ProductNoramlTexture::~ProductNoramlTexture()
{
    if(GLProgram__)
    {
        delete GLProgram__;
        GLProgram__ = nullptr;
    }

    if(texture2D_)
    {
        delete texture2D_;
        texture2D_ = nullptr;
    }
}

void ProductNoramlTexture::CreateScence(Context *context, int width, int height)
{
    Context_ = context;
    File_ = Context_->getSubsystem<File>();
    std::string vertexShaderSource = File_->getStringFromFileAssets("SkySnowResources/CoreData/Shaders/ProductNormalMapVertex.glsl");
    std::string fragShaderSource = File_->getStringFromFileAssets("SkySnowResources/CoreData/Shaders/ProductNormalMapFragment.glsl");
    GLProgram__  = new GLProgram();
    GLProgram__->initWithVertexShaderString(vertexShaderSource,fragShaderSource);
    GLProgram__->addAttribute("position");
    GLProgram__->addAttribute("texCoord");
    GLProgram__->link();

    u_PositionHandle = GLProgram__->getAttributeIndex("position");
    u_TexCoordsHandle = GLProgram__->getAttributeIndex("texCoord");
    u_ImageHandle = GLProgram__->getUniformIndex("colorMap");
    u_ImageSizeHandle = GLProgram__->getUniformIndex("imageSize");

    texture2D_ = new Texture2D(context);
    Image* image = new Image(context);
    image->loadImage("/sdcard/SkySnowResources/CoreData/Textures/fish.png");
    texture2D_->setData(image);

    RectScreen_ = new RectScreen();
    imageSize_ = new float[2];
    imageSize_[0] = 128.0f;
    imageSize_[1] = 128.0f;
}

void ProductNoramlTexture::Renderer()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);
    glDisable(GL_DEPTH_TEST);
    glUseProgram(GLProgram__->getProgramId());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture2D_->getGPUObjectName());
    glUniform1i(u_ImageHandle,0);

    glEnableVertexAttribArray(u_PositionHandle);
    glEnableVertexAttribArray(u_TexCoordsHandle);

    glVertexAttribPointer(u_PositionHandle, 2, GL_FLOAT, GL_FALSE, 0,RectScreen_->positions);
    glVertexAttribPointer(u_TexCoordsHandle, 2, GL_FLOAT, GL_FALSE, 0, RectScreen_->texcoords);

    glUniform2fv(u_ImageSizeHandle, 1, imageSize_);
    glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT,RectScreen_->index);

    glBindTexture(GL_TEXTURE_2D,0);
    glUseProgram(0);
}

bool ProductNoramlTexture::SaveNormalTexture()
{

}