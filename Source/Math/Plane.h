//
// Created by liuqian8 on 2019/6/25.
//
#pragma once

#include <glm/ext.hpp>
#include "vec4.hpp"
#include "vec3.hpp"
#include "mat4x4.hpp"
#include "type_ptr.hpp"
#include <vector>
#include "MeshData.h"
class Plane
{
public:
    Plane();

    ~Plane();

    void setScale(float scale);

    void setTransform(glm::vec3 transform);

    void setRotation(glm::mat4 rotationMat);

    std::vector<MeshData> getPlaneData()
    {
        return planeData_;
    }

    std::vector<int> getPlaneIndex()
    {
        return indexs_;
    }
private:
    void initial();
    float scale_;
    std::vector<MeshData> planeData_;
    std::vector<int> indexs_;
};
