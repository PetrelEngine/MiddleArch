//
// Created by liuqian8 on 2019/6/25.
//
#include "CubeBox.h"

CubeBox::CubeBox(float radius)
{

}

CubeBox::~CubeBox()
{
//    delete[] cubeData;
}

void CubeBox::initial(float radius)
{
//    cubeData =
//    {
//            // back face
//            -1.0f * radius, -1.0f * radius, -1.0f * radius,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
//            1.0f * radius,  1.0f * radius, -1.0f * radius,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
//            1.0f * radius, -1.0f * radius, -1.0f * radius,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right
//            1.0f * radius,  1.0f * radius, -1.0f * radius,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
//            -1.0f * radius, -1.0f * radius, -1.0f * radius,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
//            -1.0f * radius,  1.0f * radius, -1.0f * radius,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
//            // front face
//            -1.0f * radius, -1.0f * radius,  1.0f * radius,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
//            1.0f * radius, -1.0f * radius,  1.0f * radius,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
//            1.0f * radius,  1.0f * radius,  1.0f * radius,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
//            1.0f * radius,  1.0f * radius,  1.0f * radius,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
//            -1.0f * radius,  1.0f * radius,  1.0f * radius,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
//            -1.0f * radius, -1.0f * radius,  1.0f * radius,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
//            // left face
//            -1.0f * radius,  1.0f * radius,  1.0f * radius, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
//            -1.0f * radius,  1.0f * radius, -1.0f * radius, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
//            -1.0f * radius, -1.0f * radius, -1.0f * radius, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
//            -1.0f * radius, -1.0f * radius, -1.0f * radius, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
//            -1.0f * radius, -1.0f * radius,  1.0f * radius, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
//            -1.0f * radius,  1.0f * radius,  1.0f * radius, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
//            // right face
//            1.0f * radius,  1.0f * radius,  1.0f * radius,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
//            1.0f * radius, -1.0f * radius, -1.0f * radius,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
//            1.0f * radius,  1.0f * radius, -1.0f * radius,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right
//            1.0f * radius, -1.0f * radius, -1.0f * radius,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
//            1.0f * radius,  1.0f * radius,  1.0f * radius,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
//            1.0f * radius, -1.0f * radius,  1.0f * radius,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left
//            // bottom face
//            -1.0f * radius, -1.0f * radius, -1.0f * radius,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
//            1.0f * radius, -1.0f * radius, -1.0f * radius,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
//            1.0f * radius, -1.0f * radius,  1.0f * radius,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
//            1.0f * radius, -1.0f * radius,  1.0f * radius,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
//            -1.0f * radius, -1.0f * radius,  1.0f * radius,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
//            -1.0f * radius, -1.0f * radius, -1.0f * radius,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
//            // top face
//            -1.0f * radius,  1.0f * radius, -1.0f * radius,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
//            1.0f * radius,  1.0f * radius , 1.0f * radius,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
//            1.0f * radius,  1.0f * radius, -1.0f * radius,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right
//            1.0f * radius,  1.0f * radius,  1.0f * radius,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
//            -1.0f * radius,  1.0f * radius, -1.0f * radius,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
//            -1.0f * radius,  1.0f * radius,  1.0f * radius,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left
//    };
}
