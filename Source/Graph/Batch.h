//
// Created by liuqian8 on 2019/6/4.
//
#pragma once

#include "DataStruct.h"
#include "type_mat.hpp"
#include "type_mat4x4.hpp"
#include "Drawable.h"
class View;
class Geometry;
class ShaderVariation;
class Drawable;
//Queued 3D geometry draw call.
struct Batch
{
    Batch()
    {
    }

    Batch(const SourceBatch& rhs):
            geometry_(rhs.geometry_),
            modelmatrix_(rhs.wordTransform_)
    {
    }

    void Prepare(View* view);

    void Draw(View* view);

    glm::mat4        modelmatrix_;

    Geometry*        geometry_;

    ShaderVariation* vertexShader_;

    ShaderVariation* pixelShader_;
};

struct BatchGroup:public Batch
{
    BatchGroup():
            startIndex_(M_MAX_UNSIGNED)
    {
    }

    BatchGroup(const Batch& batch):
            Batch(batch),
            startIndex_(M_MAX_UNSIGNED)
    {
    }

    ~BatchGroup()
    {

    }

    void Draw(View* view, bool allowDepthWrite) const;
    unsigned startIndex_;
};
