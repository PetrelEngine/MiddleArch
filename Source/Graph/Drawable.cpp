//
// Created by liuqian8 on 2019/6/6.
//
#include "Drawable.h"

SourceBatch::SourceBatch():
    geometry_(nullptr),
    wordTransform_(glm::mat4(1.0))
{

}

SourceBatch::SourceBatch(const SourceBatch &batch)
{
    *this = batch;
}

SourceBatch::~SourceBatch()
{

}

SourceBatch& SourceBatch::operator=(const SourceBatch &rhs)
{
    geometry_ = rhs.geometry_;
    wordTransform_ = rhs.wordTransform_;
    return *this;
}
