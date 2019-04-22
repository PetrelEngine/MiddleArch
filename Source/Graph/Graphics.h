//
// Created by liuqian8 on 2019/4/22.
//

#pragma once
#include "Object.h"
class Graphics:public Object
{
ENGINE_OBJECT(Graphics,Object);
public:
    Graphics(Context* context);
    virtual ~Graphics();
};
