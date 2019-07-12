//
// Created by liuqian8 on 2019/7/12.
//
#pragma once
#include "Drawable.h"

class Zone: public Drawable
{
    ENGINE_OBJECT(Zone,Drawable);
public:
    Zone(Context* context);

    virtual ~Zone();
};
