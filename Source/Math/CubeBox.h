//
// Created by liuqian8 on 2019/6/25.
//
#pragma once
#include "MeshData.h"
#include <vector>

class CubeBox
{
public:
    CubeBox(float radius);

    ~CubeBox();

    float* getCubedata()
    {
        return cubeData;
    }

private:
    void initial(float radius);

    float cubeData[];
};
