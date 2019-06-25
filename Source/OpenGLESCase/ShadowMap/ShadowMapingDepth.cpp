//
// Created by liuqian8 on 2019/5/23.
//
#include "ShadowMapingDepth.h"
#include "Shader.h"
#include "Image.h"
#define Sdcard "/sdcard/SkySnowResources/CoreData/Shaders/"
ShadowMapingDepth::ShadowMapingDepth()
{

}

ShadowMapingDepth::~ShadowMapingDepth()
{

}

void ShadowMapingDepth::CreateScence(Context *context, int width, int height)
{
    file_ = context->getSubsystem<File>();

    //将几何数据渲染到深度图中
    string depth_Vs = file_->getStringFromFile(Sdcard+'shadow_map_depth_vs.glsl');
    string depth_Fs = file_->getStringFromFile(Sdcard+'shadow_map_depth_fs.glsl');
    GLProgram_depth_  = new GLProgram();
    GLProgram_depth_->initWithVertexShaderString(depth_Vs,depth_Fs);
    GLProgram_depth_->addAttribute("positions");
    GLProgram_depth_->link();

    //将深度渲染出来
    string depth_use_Vs = file_->getStringFromFile(Sdcard+'shadow_map_use_vs.glsl');
    string depth_use_Fs = file_->getStringFromFile(Sdcard+'shadow_map_use_fs.glsl');
    GLProgram_use_depth_  = new GLProgram();
    GLProgram_use_depth_->initWithVertexShaderString(depth_Vs,depth_Fs);
    GLProgram_use_depth_->addAttribute("positions");
    GLProgram_use_depth_->addAttribute("texCoords");
    GLProgram_use_depth_->link();

    //平面的纹理加载
    texture_ = new Texture2D(context);
    Image* image = new Image(context);
    image->loadImage("/sdcard/SkySnowResources/CoreData/Textures/wood.png");
    texture_->setData(image);

    initialPlane();
    initialCubeBox();
}



void ShadowMapingDepth::RenderScence()
{

}

void ShadowMapingDepth::Move()
{

}

void ShadowMapingDepth::initialPlane()
{
    plane_ = new Plane();
    unsigned planeVBO;
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, 4 * 8 * sizeof(float), plane_->getPlaneData().data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glBindVertexArray(0);
}

void ShadowMapingDepth::RenderCube()
{
    cubeBox_ = new CubeBox(1.0f);
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    // fill buffer
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, 6 * 8 * sizeof(float), cubeBox_->getCubedata(), GL_STATIC_DRAW);
    // link vertex attributes
    glBindVertexArray(cubeVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void ShadowMapingDepth::RenderPlane()
{

}
