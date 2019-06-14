//
// Created by liuqian8 on 2019/6/14.
//
#pragma once

#include "Object.h"

class Camera : public Object
{
    ENGINE_OBJECT(Camera,Object);
public:
    Camera(Context* context);

    virtual ~Camera();

protected:


private:

};
