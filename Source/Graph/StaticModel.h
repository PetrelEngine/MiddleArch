//
// Created by liuqian8 on 2019/7/10.
//
#pragma once
#include "Drawable.h"
class Model;

class StaticModel: public Drawable
{
    ENGINE_OBJECT(StaticModel,Drawable);
public:
    StaticModel(Context* context);

    virtual ~StaticModel();

    virtual void updateBatches(const FrameInfo& frame) override;

    virtual void setMaterial(Material* material);

    virtual bool setMaterial(unsigned index,Material* material);

    virtual void setModel(Model* model);
};
