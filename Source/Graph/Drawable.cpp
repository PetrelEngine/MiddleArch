//
// Created by liuqian8 on 2019/6/6.
//
#include "Drawable.h"
#include "Material.h"
SourceBatch::SourceBatch():
    geometry_(nullptr),
    wordTransform_(glm::mat4(1.0)),
    distance_(0.0f),
    instancingData_(NULL),
    material_(NULL),
    numWorldTransforms_(1)
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



Drawable::Drawable(Context *context):
    Component(context)
{

}

Drawable::~Drawable()
{

}

void Drawable::updateBatches(const FrameInfo& frame)
{

}
