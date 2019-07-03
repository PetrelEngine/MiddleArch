//
// Created by liuqian8 on 2019/5/22.
//
#include "matrix_transform.hpp"
#include "NormalMap.h"
#include <glm/ext.hpp>
#include "Image.h"
NormalMap::NormalMap():
        texture2DD_(nullptr),
        texture2DN_(nullptr)
{
}

NormalMap::~NormalMap()
{
    if(GLProgram__)
    {
        delete GLProgram__;
        GLProgram__ = NULL;
    }

    if(texture2DD_)
    {
        delete texture2DD_;
        texture2DD_ = nullptr;
    }

    if(texture2DN_)
    {
        delete texture2DN_;
        texture2DN_ = nullptr;
    }
}

void NormalMap::CreateScence(Context * context, int width, int height)
{
    Context_ = context;
    File_ = Context_->getSubsystem<File>();
    std::string vertexShaderSource = File_->getStringFromFileAssets("SkySnowResources/CoreData/Shaders/NormalMapingVertex.glsl");
    std::string fragShaderSource = File_->getStringFromFileAssets("SkySnowResources/CoreData/Shaders/NormalMappingFragment.glsl");
    GLProgram__  = new GLProgram();

    GLProgram__->initWithVertexShaderString(vertexShaderSource,fragShaderSource);
    GLProgram__->addAttribute("positions");
    GLProgram__->addAttribute("texCoords");
    GLProgram__->addAttribute("normals");
    GLProgram__->link();
    //顶点着色器
    GraphNormal_.positionHandle = GLProgram__->getAttributeIndex("positions");
    GraphNormal_.texcoordsHandle = GLProgram__->getAttributeIndex("texCoords");
    GraphNormal_.normalHandle = GLProgram__->getAttributeIndex("normals");
    GraphNormal_.modelMatrixHandle = GLProgram__->getUniformIndex("modelMatrix");
    GraphNormal_.mvpMatrixHandle = GLProgram__->getUniformIndex("mvpMatrix");
    //片元着色器
    GraphNormal_.normalMapHandle = GLProgram__->getUniformIndex("normalMap");
    GraphNormal_.colorMapHandle = GLProgram__->getUniformIndex("colorMap");
    GraphNormal_.lightPositionHandle = GLProgram__->getUniformIndex("lightPosition");
    GraphNormal_.lightColorHandle = GLProgram__->getUniformIndex("lightColor");
    GraphNormal_.eyePositionHandle = GLProgram__->getUniformIndex("eyePosition");
    GraphNormal_.normalScalehandle = GLProgram__->getUniformIndex("normalScale");

    GraphNormal_.mvpMatrix = glm::mat4(1.0);
    GraphNormal_.modelMatrix = glm::mat4(1.0);
    GraphNormal_.cameraMatrix = glm::mat4(1.0);
    GraphNormal_.projectMatrix = glm::mat4(1.0);

    float pi = 3.1415926f;
    GraphNormal_.eyePos = glm::vec3(0,0,3);

    GraphNormal_.modelMatrix = glm::translate(glm::vec3(0,-0.5,-3))*glm::rotate(0.0f,glm::vec3(0,1,0))* glm::rotate(0.0f,glm::vec3(1,0,0))*glm::scale(glm::vec3(3.0f,3.0f,3.0f));//pi/2.0f
    GraphNormal_.cameraMatrix = glm::lookAt(GraphNormal_.eyePos,glm::vec3(0,0,0),glm::vec3(0,1,0));
    GraphNormal_.projectMatrix = glm::perspective(glm::radians(120.0f), (float)width / (float)height, 0.1f, 100.0f);
    GraphNormal_.mvpMatrix = GraphNormal_.projectMatrix*GraphNormal_.cameraMatrix* GraphNormal_.modelMatrix;
    //光照位置
    GraphNormal_.lightPos = glm::vec3(-3.0f, 0.0f, 0.0f);
    //光照颜色
    GraphNormal_.lightColor = glm::vec3(10.25);


    texture2DD_ = new Texture2D(context);
    Image* image1 = new Image(context);
    image1->loadImage("/sdcard/SkySnowResources/CoreData/Textures/bricks2.jpg");
    texture2DD_->setData(image1);

    texture2DN_ = new Texture2D(context);
    Image* image2 = new Image(context);
    image2->loadImage("/sdcard/SkySnowResources/CoreData/Textures/bricks2_normal.jpg");
    texture2DN_->setData(image2);
}

void NormalMap::RenderScence()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
    glUseProgram(GLProgram__->getProgramId());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture2DD_->getGPUObjectName());
    glUniform1i(GraphNormal_.colorMapHandle,0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,texture2DN_->getGPUObjectName());
    glUniform1i(GraphNormal_.normalMapHandle,1);

    glEnableVertexAttribArray(GraphNormal_.positionHandle);
    glEnableVertexAttribArray(GraphNormal_.normalHandle);
    glEnableVertexAttribArray(GraphNormal_.texcoordsHandle);

    glVertexAttribPointer(GraphNormal_.positionHandle, 3, GL_FLOAT, GL_FALSE, 0, Rect3D_.positions);
    glVertexAttribPointer(GraphNormal_.normalHandle, 3, GL_FLOAT, GL_FALSE,0, Rect3D_.normals);
    glVertexAttribPointer(GraphNormal_.texcoordsHandle, 2, GL_FLOAT, GL_FALSE, 0, Rect3D_.texcoords);

    glUniform3fv(GraphNormal_.lightPositionHandle, 1, (float*)&GraphNormal_.lightPos);
    glUniform3fv(GraphNormal_.lightColorHandle, 1, (float*)&GraphNormal_.lightColor);

    glUniform1f(GraphNormal_.normalScalehandle,GraphNormal_.normalScale);

    glUniform3fv(GraphNormal_.eyePositionHandle, 1, (float*)&GraphNormal_.eyePos);

    glUniformMatrix4fv(GraphNormal_.mvpMatrixHandle, 1, false, (GLfloat *)&GraphNormal_.mvpMatrix);
    glUniformMatrix4fv(GraphNormal_.modelMatrixHandle, 1, false, (GLfloat *)&GraphNormal_.modelMatrix);
    glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT,Rect3D_.index);

    glBindTexture(GL_TEXTURE_2D,0);
    glUseProgram(0);
    glDisable(GL_DEPTH_TEST);
}

void NormalMap::Move()
{

}
