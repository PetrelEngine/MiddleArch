//
// Created by liuqian8 on 2019/5/21.
//
#include <glm/ext.hpp>
#include "PBR_LightingTexture.h"

PBR_LightingTexture::PBR_LightingTexture()
{

}

PBR_LightingTexture::~PBR_LightingTexture()
{
    if(File_)
    {
        delete File_;
        File_ = NULL;
    }

    if(GLProgram_)
    {
        delete GLProgram_;
        GLProgram_ = NULL;
    }

    if(Sphere_)
    {
        delete Sphere_;
        Sphere_ = NULL;
    }
}

void PBR_LightingTexture::CreateScence(Context *context, int width, int height)
{
    Context_ = context;
    //组建一个球体模型数据
    Sphere_ = new Sphere();

    File_ = new File(Context_);
    std::string vertexShaderSource = File_->getStringFromFileAssets("PBRTextureVertex.glsl");
    std::string fragShaderSource = File_->getStringFromFileAssets("PBRTextureFragment.glsl");
    GLProgram_  = new GLProgram();
    GLProgram_->initWithVertexShaderString(vertexShaderSource,fragShaderSource);
    GLProgram_->addAttribute("positions");
    GLProgram_->addAttribute("texCoords");
    GLProgram_->addAttribute("normals");
    GLProgram_->link();

    PRBGraph_.positionHandle = GLProgram_->getAttributeIndex("positions");//位置
    PRBGraph_.texCoordsHandle = GLProgram_->getAttributeIndex("texCoords");//纹理坐标
    PRBGraph_.normalHandle = GLProgram_->getAttributeIndex("normals");//法线
    PRBGraph_.modelMatrixHandle = GLProgram_->getUniformIndex("modelMatrix");//模型矩阵
    PRBGraph_.mvpMatrixHandle = GLProgram_->getUniformIndex("mvpMatrix");//mvp矩阵
    PRBGraph_.albedoMapHandle = GLProgram_->getUniformIndex("albedoMap");//反照率贴图
    PRBGraph_.normalMapHandle = GLProgram_->getUniformIndex("normalMap");//法线贴图
    PRBGraph_.metallicMapHandle = GLProgram_->getUniformIndex("metallicMap");//金属质地贴图
    PRBGraph_.roughnessMapHandle = GLProgram_->getUniformIndex("roughnessMap");//粗糙度贴图
    PRBGraph_.aoMapHandle = GLProgram_->getUniformIndex("aoMap");//
    PRBGraph_.lightPositionHandle = GLProgram_->getUniformIndex("lightPositions");//光照位置
    PRBGraph_.lightColorHandle = GLProgram_->getUniformIndex("lightColors");//光照颜色
    PRBGraph_.eyePositionHandle = GLProgram_->getUniformIndex("eyePos");//相机位置

    //组建矩阵相关数据
    PRBGraph_.mvpMatrix = glm::mat4(1.0);
    PRBGraph_.modelMatrix = glm::mat4(1.0);
    PRBGraph_.cameraMatrix = glm::mat4(1.0);
    PRBGraph_.projectMatrix = glm::mat4(1.0);

    float pi = 3.1415926f;
    //相机位置数据
    PRBGraph_.eyePos = glm::vec3(0,0,3);
    //组件mvp矩阵
    PRBGraph_.modelMatrix = glm::translate(glm::vec3(0,-0.5,0))*glm::rotate(0.0f,glm::vec3(0,1,0))* glm::rotate(-pi/2.0f,glm::vec3(1,0,0))*glm::scale(glm::vec3(1.0f,1.0f,1.0f));//pi/2.0f
    PRBGraph_.cameraMatrix = glm::lookAt(PRBGraph_.eyePos,glm::vec3(0,0,0),glm::vec3(0,1,0));
    PRBGraph_.projectMatrix = glm::perspective(glm::radians(120.0f), (float)width / (float)height, 0.1f, 100.0f);
    PRBGraph_.mvpMatrix = PRBGraph_.projectMatrix*PRBGraph_.cameraMatrix* PRBGraph_.modelMatrix;
    //光照位置
    PRBGraph_.lightPos[0] = glm::vec3(3.0f, 0.0f, 3.0f);
    PRBGraph_.lightPos[1] = glm::vec3(-3.0f, 0.0f, 3.0f);
    PRBGraph_.lightPos[2] = glm::vec3 (3.0f, 0.0f, -3.0f);
    PRBGraph_.lightPos[3] = glm::vec3 (-3.0f, 0.0f, -3.0f);
    //光照颜色
    PRBGraph_.lightColor[0] = glm::vec3(100.0f);
    PRBGraph_.lightColor[1] = glm::vec3(100.0f);
    PRBGraph_.lightColor[2] = glm::vec3(100.0f);
    PRBGraph_.lightColor[3] = glm::vec3(100.0f);
    //生锈的铁球
//    PRBGraph_.albedoMapId = Context_->getTextureId("iron_albedo");
//    PRBGraph_.aoMapId = Context_->getTextureId("iron_ao");
//    PRBGraph_.metallicMapId = Context_->getTextureId("iron_metallic");
//    PRBGraph_.normalMapId = Context_->getTextureId("iron_normal");
//    PRBGraph_.roughnessMapId = Context_->getTextureId("iron_roughness");
    //墙体
    PRBGraph_.albedoMapId = Context_->getTextureId("wall_albedo");
    PRBGraph_.aoMapId = Context_->getTextureId("wall_ao");
    PRBGraph_.metallicMapId = Context_->getTextureId("wall_metallic");
    PRBGraph_.normalMapId = Context_->getTextureId("wall_normal");
    PRBGraph_.roughnessMapId = Context_->getTextureId("wall_roughness");

    //创建VAO
    glGenVertexArrays(1, &PRBGraph_.vaoId);

    unsigned int vbo, ebo;
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(PRBGraph_.vaoId);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, Sphere_->getData().size() * sizeof(float), &Sphere_->getData()[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Sphere_->getIndex().size() * sizeof(unsigned int), &Sphere_->getIndex()[0], GL_STATIC_DRAW);
    float stride = (3 + 2 + 3) * sizeof(float);
    glEnableVertexAttribArray(PRBGraph_.positionHandle);
    glVertexAttribPointer(PRBGraph_.positionHandle, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(PRBGraph_.texCoordsHandle);
    glVertexAttribPointer(PRBGraph_.texCoordsHandle, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(PRBGraph_.normalHandle);
    glVertexAttribPointer(PRBGraph_.normalHandle, 3, GL_FLOAT, GL_FALSE, stride, (void*)(5 * sizeof(float)));
}

void PBR_LightingTexture::move()
{
    //计算相机的z轴的位置
    float pi = 3.1415926f;
    PRBGraph_.eyePos = glm::vec3(3 * cosf(count * (pi/50)),0,3 * sinf(count * (pi/50)));
    PRBGraph_.cameraMatrix = glm::lookAt(PRBGraph_.eyePos,glm::vec3(0,0,0),glm::vec3(0,1,0));
    PRBGraph_.mvpMatrix = PRBGraph_.projectMatrix*PRBGraph_.cameraMatrix* PRBGraph_.modelMatrix;
    count ++;
    count = count % 360;
}

void PBR_LightingTexture::RenderScence()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
    glUseProgram(GLProgram_->getProgramId());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, PRBGraph_.albedoMapId);
    glUniform1i(PRBGraph_.albedoMapHandle,0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, PRBGraph_.aoMapId);
    glUniform1i(PRBGraph_.aoMapHandle,1);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, PRBGraph_.metallicMapId);
    glUniform1i(PRBGraph_.metallicMapHandle,2);

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, PRBGraph_.normalMapId);
    glUniform1i(PRBGraph_.normalMapHandle,3);

    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, PRBGraph_.roughnessMapId);
    glUniform1i(PRBGraph_.roughnessMapHandle,4);

    glUniform3fv(PRBGraph_.lightPositionHandle, 4, (float*)&PRBGraph_.lightPos);
    glUniform3fv(PRBGraph_.lightColorHandle, 4, (float*)&PRBGraph_.lightColor);

    glUniform3fv(PRBGraph_.eyePositionHandle, 1, (float*)&PRBGraph_.eyePos);

    glUniformMatrix4fv(PRBGraph_.mvpMatrixHandle, 1, false, (GLfloat *)&PRBGraph_.mvpMatrix);
    glUniformMatrix4fv(PRBGraph_.modelMatrixHandle, 1, false, (GLfloat *)&PRBGraph_.modelMatrix);
    glBindVertexArray(PRBGraph_.vaoId);
    glDrawElements(GL_TRIANGLE_STRIP,Sphere_->getIndexCount(),GL_UNSIGNED_INT,0);

    glBindTexture(GL_TEXTURE_2D,0);
    glUseProgram(0);
    glDisable(GL_DEPTH_TEST);
}
