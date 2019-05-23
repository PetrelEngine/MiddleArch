//
// Created by liuqian8 on 2019/5/23.
//

#pragma once

#include "Object.h"

class Graphics: public Object
{
    ENGINE_OBJECT(Graphics,Object);
public:

    Graphics(Context* context);

    ~Graphics();

    void SetVBO(unsigned object);

    void DrawElements();

    void DrawArrays();

protected:

};
