//
// Created by liuqian8 on 2019/4/17.
//
#include <glm/ext.hpp>
#include "PBRSample.h"
#include "File.h"
PBRSample::PBRSample():
    Context_(NULL),
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
    bool loadout = loadObj_->ParseObj("/sdcard/PBRObj/Box/box_stack.obj");


//    PositionData_ = model_.vertex;
//    TexCoordData_ = model_.texCoord;
//    NormalData_ = model_.normal;
//    TexCoordData_ = loadObj_->getTexCoord();
//    NormalData_ = loadObj_->getNormal();
//    IndexData_ = loadObj_ ->getIndices();
//    if(loadout)
//    {
//        LOGI("OBJ模型加载成功。");
//    }else{
//        LOGI("OBJ模型加载失败。");
//    }
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

    MVPMatrix_ = glm::mat4(1.0);
    ModelMatrix_ = glm::mat4(1.0);
    CameraMatrix_ = glm::mat4(1.0);
    ProjectMatrix_ = glm::mat4(1.0);

//    ModelMatrix_ = glm::translate(glm::vec3(0,0,-40));
    ModelMatrix_ = glm::scale(glm::vec3(1.1,1.1,1.1));
    CameraMatrix_ = glm::lookAt(glm::vec3(0,0,0),glm::vec3(0,0,-1),glm::vec3(0,1,0));
    ProjectMatrix_ = glm::ortho(-1,1,-1,1,1,100);

    MVPMatrix_ = ProjectMatrix_*CameraMatrix_* ModelMatrix_;
}

void PBRSample::RenderOneFrame(Context *context)
{
    if(ShaderProgram_ == NULL)
        return;

//    glUseProgram(ShaderProgram_->ID);
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, 1);
//    glUniform1i(TextureHandle_,0);
//
//    glVertexAttribPointer(PositionHandle_, 2, GL_FLOAT, GL_FALSE, 0, &PositionData_);
//    glVertexAttribPointer(TexcoordHandle_, 2, GL_FLOAT, GL_FALSE, 0, &TexCoordData_);
//    glVertexAttribPointer(NormalHandle_, 3, GL_FLOAT, GL_FALSE, 0, &NormalData_);
//
//    glUniformMatrix4fv(MVPMatrixHandle_, 1, false, (GLfloat *)&MVPMatrix_);
//    glEnableVertexAttribArray(PositionHandle_);
//    glEnableVertexAttribArray(TexcoordHandle_);
//    glEnableVertexAttribArray(NormalHandle_);
////    glDrawElements(GL_TRIANGLE_FAN, loadObj_->indexsSize(),GL_UNSIGNED_INT,IndexData_);//GL_QUADS
//    glDrawArrays(GL_TRIANGLES, 0,PositionData_.size()/3);
//    glBindTexture(GL_TEXTURE_2D, 0);
//    glUseProgram(0);
}
