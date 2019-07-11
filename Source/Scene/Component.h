//
// Created by liuqian8 on 2019/7/10.
//
#pragma once
#include "Animatable.h"

class Component:public Animatable
{
    ENGINE_OBJECT(Component,Animatable);
public:
    Component(Context* context);

    virtual ~Component();
};
