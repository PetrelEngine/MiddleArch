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
    bool loadout = loadObj_->LoadFile("/sdcard/PBRObj/Box/box_stack.obj");
    if(loadout)
    {
        LOGI("OBJ模型加载成功。");
    }else{
        LOGI("OBJ模型加载失败。");
    }

    for(int i = 0; i < loadObj_->LoadedMeshes.size(); i++)
    {
        Mesh curMesh = loadObj_->LoadedMeshes[i];
        for (int j = 0; j < curMesh.Indices.size(); j += 3)
        {
            LOGI("索引打印：%d,%d,%d",curMesh.Indices[j],curMesh.Indices[j+1],curMesh.Indices[j+2]);
        }
    }

    for(int i = 0; i < loadObj_->LoadedIndices.size();i ++)
    {
        LOGI("LoadedIndices::索引打印：%d,%d,%d",loadObj_->LoadedIndices[i],loadObj_->LoadedIndices[i+1],loadObj_->LoadedIndices[i+2]);
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

    MVPMatrix_ = glm::mat4(1.0);
    ModelMatrix_ = glm::mat4(1.0);
    CameraMatrix_ = glm::mat4(1.0);
    ProjectMatrix_ = glm::mat4(1.0);

//    ModelMatrix_ = glm::translate(glm::vec3(0,0,-40));
    ModelMatrix_ = glm::scale(glm::vec3(1.1,1.1,1.1));
    CameraMatrix_ = glm::lookAt(glm::vec3(0,0,0),glm::vec3(0,0,-1),glm::vec3(0,1,0));
    ProjectMatrix_ = glm::ortho(-1,1,-1,1,1,100);

    MVPMatrix_ = ProjectMatrix_*CameraMatrix_* ModelMatrix_;


    for(int i = 0; i < 3; i ++)
    {
        m_VboIds[i] = 0;
    }

    GLuint m_VboIds[3];

    glGenBuffers(3, m_VboIds);

    //存放顶点位置数据
    glBindBuffer(GL_ARRAY_BUFFER, m_VboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(Vector3), &loadObj_->LoadedMeshes[0].Vertices, GL_STATIC_DRAW);

    //存放uv数据
    glBindBuffer(GL_ARRAY_BUFFER, m_VboIds[1]);
    glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(Vector2), &loadObj_->LoadedMeshes[0].Vertices, GL_STATIC_DRAW);

    //存放顶点索引
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VboIds[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint), &loadObj_->LoadedMeshes[0].Indices, GL_STATIC_DRAW);
}

void PBRSample::RenderOneFrame(Context *context)
{
    if(ShaderProgram_ == NULL)
        return;

    glUseProgram(ShaderProgram_->ID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 1);
    glUniform1i(TextureHandle_,0);
//
//    glVertexAttribPointer(PositionHandle_, 3, GL_FLOAT, GL_FALSE, 0, PositionData_);
//    glVertexAttribPointer(TexcoordHandle_, 2, GL_FLOAT, GL_FALSE, 0, TexCoordData_);
//    glVertexAttribPointer(NormalHandle_, 3, GL_FLOAT, GL_FALSE, 0, NormalData_);
//
//    glUniformMatrix4fv(MVPMatrixHandle_, 1, false, (GLfloat *)&MVPMatrix_);
//    glEnableVertexAttribArray(PositionHandle_);
//    glEnableVertexAttribArray(TexcoordHandle_);
//    glEnableVertexAttribArray(NormalHandle_);
//    glDrawElements(GL_TRIANGLES, loadObj_->getSize(),GL_UNSIGNED_INT,IndexData_);//GL_QUADS  GL_TRIANGLE_FAN  GL_TRIANGLES
////    glDrawArrays(GL_TRIANGLES, 0,PositionData_.size()/3);
//    glBindTexture(GL_TEXTURE_2D, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_VboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(Vector3), &loadObj_->LoadedMeshes[0].Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(PositionHandle_, 3, GL_FLOAT, false, sizeof(Vector3), 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_VboIds[1]);
    glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(Vector2), &loadObj_->LoadedMeshes[0].Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(TexcoordHandle_, 2, GL_FLOAT, false, sizeof(Vector2), 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VboIds[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint), &loadObj_->LoadedMeshes[0].Indices, GL_STATIC_DRAW);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glUseProgram(0);
}
