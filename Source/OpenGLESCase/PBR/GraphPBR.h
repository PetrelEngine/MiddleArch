//
// Created by liuqian8 on 2019/5/21.
//
#pragma once

#include "type_mat.hpp"
#include "type_mat4x4.hpp"
#include "vec3.hpp"
#include "Common.h"
struct PRBGraph
{
    GLuint      positionHandle;
    GLuint      texCoordsHandle;
    GLuint      normalHandle;
    GLuint      modelMatrixHandle;
    GLuint      mvpMatrixHandle;
    GLuint      albedoMapHandle;
    GLuint      normalMapHandle;
    GLuint      metallicMapHandle;
    GLuint      roughnessMapHandle;
    GLuint      aoMapHandle;
    GLuint      lightPositionHandle;
    GLuint      lightColorHandle;
    GLuint      eyePositionHandle;

    GLuint      vaoId;

    glm::mat4    modelMatrix;
    glm::mat4    cameraMatrix;
    glm::mat4    projectMatrix;
    glm::mat4    mvpMatrix;
    int          albedoMapId;
    int          normalMapId;
    int          metallicMapId;
    int          roughnessMapId;
    int          aoMapId;
    glm::vec3    lightPos[4];
    glm::vec3    lightColor[4];
    glm::vec3    eyePos;
};
