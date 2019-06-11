//
// Created by liuqian8 on 2019/6/6.
//

#pragma once

#include "type_mat.hpp"
#include "type_mat4x4.hpp"

class Geometry;

struct SourceBatch
{
    SourceBatch();

    SourceBatch(const SourceBatch& batch);

    ~SourceBatch();

    SourceBatch& operator=(const SourceBatch& rhs);

    Geometry* geometry_;

    glm::mat4 wordTransform_;
};
