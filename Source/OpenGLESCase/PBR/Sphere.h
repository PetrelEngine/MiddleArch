//
// Created by liuqian8 on 2019/5/21.
//
#pragma once

#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

class Sphere
{
public:
    Sphere();

    ~Sphere();

    std::vector<float> getData()
    {
        return Data_;
    }

    std::vector<unsigned int> getIndex()
    {
        return Indices_;
    }

    int getIndexCount()
    {
        return indexCount;
    }

private:
    void ProductSphere();

protected:
    int                         indexCount;
    std::vector<float>          Data_;
    std::vector<glm::vec3>      Positions_;
    std::vector<glm::vec2>      Uv_;
    std::vector<glm::vec3>      Normals_;
    std::vector<unsigned int>   Indices_;
};
