//
// Created by liuqian8 on 2019/5/14.
//
#include "ext.hpp"
#include "ParallaxMapping.h"

ParallaxMapping::ParallaxMapping()
{

}

ParallaxMapping::~ParallaxMapping()
{

}

void ParallaxMapping::CreateScence(Context *context, int width, int height)
{
    Context_ = context;
    File_ = new File(Context_);
    std::string vertexShaderSource = File_->getStringFromFileAssets("ParallaxMappingVertex.glsl");
    //ParallaxMappingFragment 是基础的视察贴图    ParallaxMapSteepFragment是陡峭的视察贴图  ParallaxOcclusionMappingFragment是视察遮蔽贴图
    std::string fragShaderSource = File_->getStringFromFileAssets("ParallaxOcclusionMappingFragment.glsl");
    GLProgram__  = new GLProgram();

    GLProgram__->initWithVertexShaderString(vertexShaderSource,fragShaderSource);
    GLProgram__->addAttribute("position");
    GLProgram__->addAttribute("texCoords");
    GLProgram__->addAttribute("tangent");
    GLProgram__->addAttribute("bitgent");
    GLProgram__->link();

    GraphParallax_.positionHandle = GLProgram__->getAttributeIndex("position");
    GraphParallax_.texcoordsHandle = GLProgram__->getAttributeIndex("texCoords");
    GraphParallax_.tangentHandle = GLProgram__->getAttributeIndex("tangent");
    GraphParallax_.bitgentHandle = GLProgram__->getAttributeIndex("bitgent");
    GraphParallax_.eyePosHandle = GLProgram__->getUniformIndex("eyePos");
    GraphParallax_.lightPosHandle = GLProgram__->getUniformIndex("lightPos");
    GraphParallax_.diffuseMapHandle = GLProgram__->getUniformIndex("diffuseMap");
    GraphParallax_.depthMapHandle = GLProgram__->getUniformIndex("dispMap");
    GraphParallax_.normalMapHandle = GLProgram__->getUniformIndex("normalMap");
    GraphParallax_.modelMatrixHandle = GLProgram__->getUniformIndex("modelMatrix");
    GraphParallax_.MVPMatrixHandle = GLProgram__->getUniformIndex("mvpMatrix");
    GraphParallax_.heightScaleHandle = GLProgram__->getUniformIndex("heightScale");

    GraphParallax_.diffuseMapTextureId = Context_->getTextureId("bri_diffuse");
    GraphParallax_.depthMapTextureId = Context_->getTextureId("bri_disp");
    GraphParallax_.normalMapTextureId = Context_->getTextureId("bri_normal");

    GraphParallax_.MVPMatrix_ = glm::mat4(1.0);
    GraphParallax_.modelMatrix_ = glm::mat4(1.0);
    GraphParallax_.CameraMatrix_ = glm::mat4(1.0);
    GraphParallax_.ProjectMatrix_ = glm::mat4(1.0);

    float pi = 3.1415926f;
    glm::vec3 eyePos = glm::vec3(0,0,8);
    glm::vec3 lightPos = glm::vec3(3,3,4);

    GraphParallax_.modelMatrix_ = glm::translate(glm::vec3(0,0,3))*glm::rotate(0.0f,glm::vec3(0,1,0))* glm::rotate(0.0f,glm::vec3(1,0,0))*glm::scale(glm::vec3(2.0f,2.0f,2.0f));
    GraphParallax_.CameraMatrix_ = glm::lookAt(eyePos,glm::vec3(0,0,-1),glm::vec3(0,1,0));
    GraphParallax_.ProjectMatrix_ = glm::perspective(glm::radians(120.0f), (float)width / (float)height, 0.1f, 100.0f);

    GraphParallax_.MVPMatrix_ = GraphParallax_.ProjectMatrix_*GraphParallax_.CameraMatrix_* GraphParallax_.modelMatrix_;

    GraphParallax_.lightPos = new float[3];
    GraphParallax_.lightPos[0] = lightPos.x;
    GraphParallax_.lightPos[1] = lightPos.y;
    GraphParallax_.lightPos[2] = lightPos.z;
    GraphParallax_.eyePos = new float[3];
    GraphParallax_.eyePos[0] = eyePos.x;
    GraphParallax_.eyePos[1] = eyePos.y;
    GraphParallax_.eyePos[2] = eyePos.z;

    Rect3D_ = new Rect3D();
    CaTangentBitgent();
}

void ParallaxMapping::CaTangentBitgent()
{
    // positions
    glm::vec3 pos1(-1.0f,  1.0f, 0.0f);
    glm::vec3 pos2(-1.0f, -1.0f, 0.0f);
    glm::vec3 pos3( 1.0f, -1.0f, 0.0f);
    glm::vec3 pos4( 1.0f,  1.0f, 0.0f);
    // texture coordinates
    glm::vec2 uv1(0.0f, 1.0f);
    glm::vec2 uv2(0.0f, 0.0f);
    glm::vec2 uv3(1.0f, 0.0f);
    glm::vec2 uv4(1.0f, 1.0f);
    // normal vector
    glm::vec3 nm(0.0f, 0.0f, 1.0f);

    // calculate tangent/bitangent vectors of both triangles
    glm::vec3 tangent1, bitangent1;
    glm::vec3 tangent2, bitangent2;
    // triangle 1
    // ----------
    glm::vec3 edge1 = pos2 - pos1;
    glm::vec3 edge2 = pos3 - pos1;
    glm::vec2 deltaUV1 = uv2 - uv1;
    glm::vec2 deltaUV2 = uv3 - uv1;

    float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
    tangent1 = glm::normalize(tangent1);

    bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
    bitangent1 = glm::normalize(bitangent1);

    // triangle 2
    // ----------
    edge1 = pos3 - pos1;
    edge2 = pos4 - pos1;
    deltaUV1 = uv3 - uv1;
    deltaUV2 = uv4 - uv1;

    f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
    tangent2 = glm::normalize(tangent2);


    bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
    bitangent2 = glm::normalize(bitangent2);

    //顶点
    Rect3D_->posArray = new float[18];
    Rect3D_->posArray[0] = pos1.x;  Rect3D_->posArray[1] = pos1.y;   Rect3D_->posArray[2] = pos1.z;
    Rect3D_->posArray[3] = pos2.x;  Rect3D_->posArray[4] = pos2.y;   Rect3D_->posArray[5] = pos2.z;
    Rect3D_->posArray[6] = pos3.x;  Rect3D_->posArray[7] = pos3.y;   Rect3D_->posArray[8] = pos3.z;

    Rect3D_->posArray[9] = pos1.x;  Rect3D_->posArray[10] = pos1.y;  Rect3D_->posArray[11] = pos1.z;
    Rect3D_->posArray[12] = pos3.x; Rect3D_->posArray[13] = pos3.y;  Rect3D_->posArray[14] = pos3.z;
    Rect3D_->posArray[15] = pos4.x; Rect3D_->posArray[16] = pos4.y;  Rect3D_->posArray[17] = pos4.z;

    //纹理坐标
    Rect3D_->texCoordsArray = new float[12];
    Rect3D_->texCoordsArray[0] = uv1.x;   Rect3D_->texCoordsArray[1] = uv1.y;
    Rect3D_->texCoordsArray[2] = uv2.x;   Rect3D_->texCoordsArray[3] = uv2.y;
    Rect3D_->texCoordsArray[4] = uv3.x;   Rect3D_->texCoordsArray[5] = uv3.y;

    Rect3D_->texCoordsArray[6] = uv1.x;   Rect3D_->texCoordsArray[7] = uv1.y;
    Rect3D_->texCoordsArray[8] = uv3.x;   Rect3D_->texCoordsArray[9] = uv3.y;
    Rect3D_->texCoordsArray[10] = uv4.x;  Rect3D_->texCoordsArray[11] = uv4.y;

    //副法线
    Rect3D_->bitgent = new float[18];
    Rect3D_->bitgent[0] = bitangent1.x;   Rect3D_->bitgent[1] = bitangent1.y;   Rect3D_->bitgent[2] = bitangent1.z;
    Rect3D_->bitgent[3] = bitangent1.x;   Rect3D_->bitgent[4] = bitangent1.y;   Rect3D_->bitgent[5] = bitangent1.z;
    Rect3D_->bitgent[6] = bitangent1.x;   Rect3D_->bitgent[7] = bitangent1.y;   Rect3D_->bitgent[8] = bitangent1.z;

    Rect3D_->bitgent[9] = bitangent2.x;   Rect3D_->bitgent[10] = bitangent2.y;  Rect3D_->bitgent[11] = bitangent2.z;
    Rect3D_->bitgent[12] = bitangent2.x;  Rect3D_->bitgent[13] = bitangent2.y;  Rect3D_->bitgent[14] = bitangent2.z;
    Rect3D_->bitgent[15] = bitangent2.x;  Rect3D_->bitgent[16] = bitangent2.y;  Rect3D_->bitgent[17] = bitangent2.z;

    //法线
    Rect3D_->tangent = new float[18];
    Rect3D_->tangent[0] = tangent1.x;   Rect3D_->tangent[1] = tangent1.y;   Rect3D_->tangent[2] = tangent1.z;
    Rect3D_->tangent[3] = tangent1.x;   Rect3D_->tangent[4] = tangent1.y;   Rect3D_->tangent[5] = tangent1.z;
    Rect3D_->tangent[6] = tangent1.x;   Rect3D_->tangent[7] = tangent1.y;   Rect3D_->tangent[8] = tangent1.z;

    Rect3D_->tangent[9] = tangent2.x;   Rect3D_->tangent[10] = tangent2.y;  Rect3D_->tangent[11] = tangent2.z;
    Rect3D_->tangent[12] = tangent2.x;  Rect3D_->tangent[13] = tangent2.y;  Rect3D_->tangent[14] = tangent2.z;
    Rect3D_->tangent[15] = tangent2.x;  Rect3D_->tangent[16] = tangent2.y;  Rect3D_->tangent[17] = tangent2.z;
}

void ParallaxMapping::RenderParallaxMapping()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);

    glUseProgram(GLProgram__->getProgramId());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, GraphParallax_.diffuseMapTextureId);
    glUniform1i(GraphParallax_.diffuseMapHandle,0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, GraphParallax_.depthMapTextureId);
    glUniform1i(GraphParallax_.depthMapHandle,1);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, GraphParallax_.normalMapTextureId);
    glUniform1i(GraphParallax_.normalMapHandle,2);

    glEnableVertexAttribArray(GraphParallax_.positionHandle);
    glEnableVertexAttribArray(GraphParallax_.texcoordsHandle);
    glEnableVertexAttribArray(GraphParallax_.tangentHandle);
    glEnableVertexAttribArray(GraphParallax_.bitgentHandle);

    glVertexAttribPointer(GraphParallax_.positionHandle, 3, GL_FLOAT, GL_FALSE, 0, Rect3D_->posArray);
    glVertexAttribPointer(GraphParallax_.texcoordsHandle, 2, GL_FLOAT, GL_FALSE,0, Rect3D_->texCoordsArray);
    glVertexAttribPointer(GraphParallax_.tangentHandle, 3, GL_FLOAT, GL_FALSE,0, Rect3D_->tangent);
    glVertexAttribPointer(GraphParallax_.bitgentHandle, 3, GL_FLOAT, GL_FALSE,0, Rect3D_->bitgent);

    glUniformMatrix4fv(GraphParallax_.MVPMatrixHandle, 1, false, (GLfloat *)&GraphParallax_.MVPMatrix_);
    glUniformMatrix4fv(GraphParallax_.modelMatrixHandle, 1, false, (GLfloat *)&GraphParallax_.modelMatrix_);

    glUniform3fv(GraphParallax_.lightPosHandle,1,GraphParallax_.lightPos);
    glUniform3fv(GraphParallax_.eyePosHandle,1,GraphParallax_.eyePos);
    glUniform1f(GraphParallax_.heightScaleHandle,GraphParallax_.heightScale);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindTexture(GL_TEXTURE_2D,0);
    glUseProgram(0);
    glDisable(GL_DEPTH_TEST);
}