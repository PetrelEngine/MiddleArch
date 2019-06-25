//
// Created by liuqian8 on 2019/6/25.
//
#include "Plane.h"

Plane::Plane():
        scale_(1.0f)
{
    initial();
}

Plane::~Plane()
{
    planeData_.clear();
    indexs_.clear();
}

void Plane::setScale(float scale)
{

}

void Plane::setTransform(glm::vec3 transform)
{

}

void Plane::setRotation(glm::mat4 rotationMat)
{

}

void Plane::initial()
{
    planeData_.clear();
    struct MeshData p1 =
    {
            glm::vec3(-10,0,-10),glm::vec2(0,1),glm::vec3(0,1,0)
    };

    struct MeshData p2 =
    {
            glm::vec3(-10,0,10),glm::vec2(0,0),glm::vec3(0,1,0)
    };

    struct MeshData p3 =
    {
            glm::vec3(10,0,10),glm::vec2(1,0),glm::vec3(0,1,0)
    };

    struct MeshData p4 =
    {
            glm::vec3(10,0,-10),glm::vec2(1,1),glm::vec3(0,1,0)
    };
    planeData_.push_back(p1);
    planeData_.push_back(p2);
    planeData_.push_back(p3);
    planeData_.push_back(p4);

    indexs_.clear();
    indexs_.push_back(1);
    indexs_.push_back(2);
    indexs_.push_back(3);

    indexs_.push_back(1);
    indexs_.push_back(3);
    indexs_.push_back(4);
}
