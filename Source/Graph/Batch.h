//
// Created by liuqian8 on 2019/6/4.
//
#pragma once

#include "type_mat.hpp"
#include "type_mat4x4.hpp"
class View;
class Geometry;
class ShaderVariation;
//Queued 3D geometry draw call.
struct Batch
{
    Batch()
    {

    }

    void Prepare(View* view);

    void Draw(View* view);

    glm::mat4        modelmatrix_;

    Geometry*        geometry_;

    ShaderVariation* vertexShader_;

    ShaderVariation* pixelShader_;
};
