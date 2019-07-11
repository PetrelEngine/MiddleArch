//
// Created by liuqian8 on 2019/7/10.
//
#include "StaticModel.h"

StaticModel::StaticModel(Context *context):
        Drawable(context)
{

}

StaticModel::~StaticModel()
{

}

void StaticModel::updateBatches(const FrameInfo &frame)
{

}

void StaticModel::setMaterial(Material *material)
{

}

bool StaticModel::setMaterial(unsigned index, Material *material)
{
    return true;
}

void StaticModel::setModel(Model *model)
{

}
