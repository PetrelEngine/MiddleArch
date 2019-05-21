//
// Created by liuqian8 on 2019/5/13.
//
#include "ProductNoramlTexture.h"

ProductNoramlTexture::ProductNoramlTexture()
{

}

ProductNoramlTexture::~ProductNoramlTexture()
{

}

void ProductNoramlTexture::CreateScence(Context *context, int width, int height)
{
    Context_ = context;
    File_ = new File(Context_);
    std::string vertexShaderSource = File_->getStringFromFileAssets("ProductNormalMapVertex.glsl");
    std::string fragShaderSource = File_->getStringFromFileAssets("ProductNormalMapFragment.glsl");
    GLProgram__  = new GLProgram();
    GLProgram__->initWithVertexShaderString(vertexShaderSource,fragShaderSource);
    GLProgram__->addAttribute("position");
    GLProgram__->addAttribute("texCoord");
    GLProgram__->link();

    u_PositionHandle = GLProgram__->getAttributeIndex("position");
    u_TexCoordsHandle = GLProgram__->getAttributeIndex("texCoord");
    u_ImageHandle = GLProgram__->getUniformIndex("colorMap");
    u_ImageSizeHandle = GLProgram__->getUniformIndex("imageSize");
    textureId_ = context->getTextureId("fish");
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
    glBindTexture(GL_TEXTURE_2D, textureId_);
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