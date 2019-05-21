//
// Created by liuqian8 on 2019/5/17.
//
#include <glm/ext.hpp>
#include <Graph/GLProgram.hpp>
#include "GammaCorrection.h"

GammaCorrection::GammaCorrection()
{

}

GammaCorrection::~GammaCorrection()
{
    if(File_)
    {
        delete File_;
        File_ = NULL;
    }

    if(GLProgram__)
    {
        delete GLProgram__;
        GLProgram__ = NULL;
    }

    if(Rect3D_)
    {
        delete Rect3D_;
        Rect3D_ = NULL;
    }
}


void GammaCorrection::CreateScence(Context *context, int width, int height)
{
    Context_ = context;
    File_ = new File(Context_);
    std::string vertexShaderSource = File_->getStringFromFileAssets("GammaCorrectionVertex.glsl");
    std::string fragShaderSource = File_->getStringFromFileAssets("GammaCorrectionFragment.glsl");
    GLProgram__  = new GLProgram();

    GLProgram__->initWithVertexShaderString(vertexShaderSource,fragShaderSource);
    GLProgram__->addAttribute("positions");
    GLProgram__->addAttribute("texcoords");
    GLProgram__->addAttribute("normals");
    GLProgram__->link();

    GraphGamma_.positionsHandle = GLProgram__->getAttributeIndex("positions");
    GraphGamma_.texCoordssHandle = GLProgram__->getAttributeIndex("texcoords");
    GraphGamma_.normalsHandle = GLProgram__->getAttributeIndex("normals");
    GraphGamma_.modelMatrixHandle = GLProgram__->getUniformIndex("modeMatrix");
    GraphGamma_.mvpMatrixHandle = GLProgram__->getUniformIndex("mvpMatrix");
    GraphGamma_.textureHandle = GLProgram__->getUniformIndex("colorMap");
    GraphGamma_.lightPosHandle = GLProgram__->getUniformIndex("lightPos");
    GraphGamma_.lightColorHandle = GLProgram__->getUniformIndex("lightColor");
    GraphGamma_.eyePosHandle = GLProgram__->getUniformIndex("eyePos");
    GraphGamma_.gammaHandle = GLProgram__->getUniformIndex("gamma");

    GraphGamma_.mvpMatrix = glm::mat4(1.0);
    GraphGamma_.modelMatrix = glm::mat4(1.0);
    GraphGamma_.cameraMatrix = glm::mat4(1.0);
    GraphGamma_.projectMatrix = glm::mat4(1.0);

    float pi = 3.1415926f;
    GraphGamma_.eyePos = glm::vec3(0,2,3);

    GraphGamma_.modelMatrix = glm::translate(glm::vec3(0,-0.5,0))*glm::rotate(0.0f,glm::vec3(0,1,0))* glm::rotate(-pi/2.0f,glm::vec3(1,0,0))*glm::scale(glm::vec3(5.0f,5.0f,5.0f));//pi/2.0f
    GraphGamma_.cameraMatrix = glm::lookAt(GraphGamma_.eyePos,glm::vec3(0,0,0),glm::vec3(0,1,0));
    GraphGamma_.projectMatrix = glm::perspective(glm::radians(120.0f), (float)width / (float)height, 0.1f, 100.0f);
    GraphGamma_.mvpMatrix = GraphGamma_.projectMatrix*GraphGamma_.cameraMatrix* GraphGamma_.modelMatrix;

    //光照位置
    GraphGamma_.lightPos[0] = glm::vec3(-3.0f, 0.0f, 0.0f);
    GraphGamma_.lightPos[1] = glm::vec3(-1.0f, 0.0f, 0.0f);
    GraphGamma_.lightPos[2] = glm::vec3 (1.0f, 0.0f, 0.0f);
    GraphGamma_.lightPos[3] = glm::vec3 (3.0f, 0.0f, 0.0f);
    //光照颜色
    GraphGamma_.lightColor[0] = glm::vec3(0.25);
    GraphGamma_.lightColor[1] = glm::vec3(0.50);
    GraphGamma_.lightColor[2] = glm::vec3(0.75);
    GraphGamma_.lightColor[3] = glm::vec3(1.00);
    //gamma 是否进行伽马吗矫正
    GraphGamma_.isGamma = true;

    //纹理Id
    GraphGamma_.texture2DId = Context_->getTextureId("gamma");
    //创建顶点、法线、纹理坐标等数据
    Rect3D_ = new Rect3D();
}

void GammaCorrection::Move()
{

}

void GammaCorrection::RenderFrame()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
    glUseProgram(GLProgram__->getProgramId());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, GraphGamma_.texture2DId);
    glUniform1i(GraphGamma_.textureHandle,0);

    glEnableVertexAttribArray(GraphGamma_.positionsHandle);
    glEnableVertexAttribArray(GraphGamma_.normalsHandle);
    glEnableVertexAttribArray(GraphGamma_.texCoordssHandle);

    glVertexAttribPointer(GraphGamma_.positionsHandle, 3, GL_FLOAT, GL_FALSE, 0, Rect3D_->positions);
    glVertexAttribPointer(GraphGamma_.normalsHandle, 3, GL_FLOAT, GL_FALSE,0, Rect3D_->normals);
    glVertexAttribPointer(GraphGamma_.texCoordssHandle, 2, GL_FLOAT, GL_FALSE, 0, Rect3D_->texcoords);

    glUniform3fv(GraphGamma_.lightPosHandle, 4, (float*)&GraphGamma_.lightPos);
    glUniform3fv(GraphGamma_.lightColorHandle, 4, (float*)&GraphGamma_.lightColor);

    glUniform3fv(GraphGamma_.eyePosHandle, 1, (float*)&GraphGamma_.eyePos);
    glUniform1i(GraphGamma_.gammaHandle,GraphGamma_.isGamma);

    glUniformMatrix4fv(GraphGamma_.mvpMatrixHandle, 1, false, (GLfloat *)&GraphGamma_.mvpMatrix);
    glUniformMatrix4fv(GraphGamma_.modelMatrixHandle, 1, false, (GLfloat *)&GraphGamma_.modelMatrix);
    glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT,Rect3D_->index);

    glBindTexture(GL_TEXTURE_2D,0);
    glUseProgram(0);
    glDisable(GL_DEPTH_TEST);
}