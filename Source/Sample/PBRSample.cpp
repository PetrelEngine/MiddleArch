//
// Created by liuqian8 on 2019/4/17.
//
#include "PBRSample.h"
#include "File.h"
PBRSample::PBRSample():
    Context_(NULL),
    loadObj_(NULL),
    ShaderProgram_(NULL)
{

}

PBRSample::~PBRSample()
{

}

void PBRSample::CreateScence(Context *context, int width, int height)
{
    Context_ = context;

    File* file = new File(Context_);

    std::string vertexShaderSource = file->getStringFromFileAssets("PBRVertex.glsl");
    std::string fragShaderSource = file->getStringFromFileAssets("PBRFragment.glsl");

    loadObj_ = new LoadObj();
    bool loadout = loadObj_->LoadFile("/sdcard/PBRObj/Box/box_stack.obj");

    PositionData_ = loadObj_->getVertices();
    TexCoordData_ = loadObj_->getTexCoord();
    NormalData_ = loadObj_->getNormal();
    IndexData_ = loadObj_ ->getIndices();
    if(loadout)
    {
        LOGI("OBJ模型加载成功。");
    }else{
        LOGI("OBJ模型加载失败。");
    }
    glViewport(0,0,width,height);

    ShaderProgram_ = new ShaderProgram(vertexShaderSource,fragShaderSource);

    PositionHandle_ = ShaderProgram_->getAttribLocation("position");
    TexcoordHandle_ = ShaderProgram_->getAttribLocation("texCoord");
    NormalHandle_ = ShaderProgram_->getAttribLocation("normal");
    TextureHandle_ = ShaderProgram_->getUniformLocation("DefaultTexture");
    MVPMatrixHandle_ = ShaderProgram_->getUniformLocation("uMVPMatix");
    glUseProgram(ShaderProgram_->ID);
    glEnableVertexAttribArray(PositionHandle_);
    glEnableVertexAttribArray(TexcoordHandle_);


}

void PBRSample::RenderOneFrame(Context *context)
{
    if(ShaderProgram_ == NULL)
        return;

    LOGE("ShaderProgram:%d",ShaderProgram_->ID);
    glUseProgram(ShaderProgram_->ID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 1);
    glUniform1i(TextureHandle_,0);

    glVertexAttribPointer(PositionHandle_, 2, GL_FLOAT, GL_FALSE, 0, &PositionData_);
    glVertexAttribPointer(TexcoordHandle_, 2, GL_FLOAT, GL_FALSE, 0, &TexCoordData_);
    glVertexAttribPointer(NormalHandle_, 2, GL_FLOAT, GL_FALSE, 0, &NormalData_);
    glEnableVertexAttribArray(PositionHandle_);
    glEnableVertexAttribArray(TexcoordHandle_);
    glEnableVertexAttribArray(NormalHandle_);
//    glDrawArrays(GL_TRIANGLES, 0, triangleCount * 3);//GL_TRIANGLES  GL_LINE_STRIP
    glDrawElements(GL_TRIANGLES,IndexData_.size(),GL_UNSIGNED_INT,&IndexData_);
    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
}
