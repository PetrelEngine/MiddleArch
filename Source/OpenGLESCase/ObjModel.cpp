//
// Created by liuqian8 on 2019/5/9.
//

#include "ObjModel.h"
#include "ShaderStr.h"

ObjModel::ObjModel()
{

}

ObjModel::~ObjModel()
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
}

void ObjModel::CreateObj(Context *context, int width, int height)
{
    Context_ = context;
//    File_ = new File(Context_);
//    std::string vertexShaderSource = File_->getStringFromFileAssets("deferredVertex.glsl");
//    std::string fragShaderSource = File_->getStringFromFileAssets("deferredFragment.glsl");
    GLProgram__  = new GLProgram();
    GLProgram__->initWithVertexShaderString(ShaderStr::deferrVertex,ShaderStr::deferrfragment);//ShaderStr::deferrVertex,ShaderStr::deferrfragment   vertexShaderSource,fragShaderSource
    GLProgram__->addAttribute("position");
    GLProgram__->addAttribute("texCoord");
    GLProgram__->addAttribute("normal");
    GLProgram__->link();


    ObjGraph_.positionHandle = GLProgram__->getAttributeIndex("position");
    ObjGraph_.texCoordHandle = GLProgram__->getAttributeIndex("texCoord");
    ObjGraph_.normalHandle = GLProgram__->getAttributeIndex("normal");
    ObjGraph_.uMVPMatixHandle = GLProgram__->getUniformIndex("uMVPMatix");
    ObjGraph_.uModelMatixHandle = GLProgram__->getUniformIndex("uModelMatix");
    ObjGraph_.DefaultTextureHandle = GLProgram__->getUniformIndex("DefaultTexture");

    loadObj_ = new LoadObj();

    bool loadout = loadObj_->LoadFile("/sdcard/PBRObj/Fish/fish.obj");
    if(loadout)
    {
        LOGI("obj 加载成功！");
    }else{
        LOGI("obj 加载失败！");
    }

    ObjGraph_.MVPMatrix_ = glm::mat4(1.0);
    ObjGraph_.ModelMatrix_ = glm::mat4(1.0);
    ObjGraph_.CameraMatrix_ = glm::mat4(1.0);
    ObjGraph_.ProjectMatrix_ = glm::mat4(1.0);

    float pi = 3.1415926f;

    ObjGraph_.ModelMatrix_ = glm::translate(glm::vec3(0,0,0))*glm::rotate(0.0f,glm::vec3(0,1,0))* glm::rotate(0.0f,glm::vec3(1,0,0))*glm::scale(glm::vec3(0.05,0.05,0.05));
    ObjGraph_.CameraMatrix_ = glm::lookAt(glm::vec3(0,1,5),glm::vec3(0,-1,-1),glm::vec3(0,1,0));
    ObjGraph_.ProjectMatrix_ = glm::frustumRH(-1,1,-1,1,1,1000);

    ObjGraph_.MVPMatrix_ = ObjGraph_.ProjectMatrix_*ObjGraph_.CameraMatrix_* ObjGraph_.ModelMatrix_;
    textureId_ = context->getTextureId("fish");

    LOGE("fish textureid:%d",textureId_);
    LOGE("GLProgram__->getProgramId():%d",GLProgram__->getProgramId());
}

void ObjModel::move()
{
    float pi = 3.1415926f;
    ObjGraph_.ModelMatrix_ = glm::translate(glm::vec3(0,0,0));
    float angle = count * (pi/50);
    ObjGraph_.ModelMatrix_ = ObjGraph_.ModelMatrix_ * glm::rotate(angle,glm::vec3(0,1,0));
    ObjGraph_.ModelMatrix_ = ObjGraph_.ModelMatrix_ * glm::scale(glm::vec3(0.05,0.05,0.05));

    ObjGraph_.MVPMatrix_ = ObjGraph_.ProjectMatrix_*ObjGraph_.CameraMatrix_* ObjGraph_.ModelMatrix_;
    count ++;
    count = count%180;
}

void ObjModel::drawObj(Context *context)
{
    glUseProgram(GLProgram__->getProgramId());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId_);
    glUniform1i(ObjGraph_.DefaultTextureHandle,0);

    glEnableVertexAttribArray(ObjGraph_.positionHandle);
    glEnableVertexAttribArray(ObjGraph_.normalHandle);
    glEnableVertexAttribArray(ObjGraph_.texCoordHandle);

    glVertexAttribPointer(ObjGraph_.positionHandle, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), loadObj_->LoadedVertices.data());
    glVertexAttribPointer(ObjGraph_.normalHandle, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (reinterpret_cast<char*>(loadObj_->LoadedVertices.data()) + 3 * sizeof(GL_FLOAT)));
    glVertexAttribPointer(ObjGraph_.texCoordHandle, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (reinterpret_cast<char*>(loadObj_->LoadedVertices.data()) + 6 * sizeof(GL_FLOAT)));

    glUniformMatrix4fv(ObjGraph_.uMVPMatixHandle, 1, false, (GLfloat *)&ObjGraph_.MVPMatrix_);
    glUniformMatrix4fv(ObjGraph_.uModelMatixHandle, 1, false, (GLfloat *)&ObjGraph_.ModelMatrix_);
    glDrawElements(GL_TRIANGLES, loadObj_->LoadedIndices.size(),GL_UNSIGNED_INT,loadObj_->LoadedIndices.data());

    glBindTexture(GL_TEXTURE_2D,0);
    glUseProgram(0);
}