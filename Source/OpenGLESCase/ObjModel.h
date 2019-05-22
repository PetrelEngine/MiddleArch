//
// Created by liuqian8 on 2019/5/9.
//

#pragma once

#include <glm/ext.hpp>
#include "LoadObj.h"
#include "GLProgram.hpp"
#include "File.h"
#include "Context.h"
#include "type_mat.hpp"
#include "type_mat4x4.hpp"

struct ObjGraph
{
    GLuint positionHandle;
    GLuint texCoordHandle;
    GLuint normalHandle;
    GLuint uMVPMatixHandle;
    GLuint uModelMatixHandle;
    GLuint DefaultTextureHandle;

    glm::mat4 ModelMatrix_;
    glm::mat4 CameraMatrix_;
    glm::mat4 ProjectMatrix_;
    glm::mat4 MVPMatrix_;
};
class ObjModel
{
public:
    ObjModel();
    ~ObjModel();

    void CreateObj(Context* context,int width,int height);

    void drawObj(Context* context);

    void move();

protected:
    Context*                    Context_;
    File*                       File_;
    GLProgram*                  GLProgram__;
    LoadObj*                    loadObj_;
    int                         textureId_;
    ObjGraph                    ObjGraph_;
    int count = 0;
};
