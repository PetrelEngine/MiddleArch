//
// Created by liuqian8 on 2019/6/4.
//
#pragma once
#include "Object.h"
class Graphics;
class Camera;
class View: public Object
{
    ENGINE_OBJECT(View,Object);
public:
    View(Context* context);

    virtual ~View();

    void setCameraShaderParameters(Camera* camera);

    void Update();

    void Render();

    Graphics* GetGraphics() const;
private:
    Graphics* graphics_;

};
