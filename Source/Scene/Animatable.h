//
// Created by liuqian8 on 2019/7/10.
//
#pragma once
#include "Serializable.h"
class Animatable:public Serializable
{
    ENGINE_OBJECT(Animatable,Serializable);
public:
    Animatable(Context* context);

    virtual ~Animatable();
};