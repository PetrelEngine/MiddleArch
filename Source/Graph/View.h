//
// Created by liuqian8 on 2019/6/4.
//
#pragma once
#include "Object.h"
#include "Batch.h"
class Graphics;
class Camera;
class Drawable;
class View: public Object
{
    ENGINE_OBJECT(View,Object);
public:
    View(Context* context);

    virtual ~View();

    void setCameraShaderParameters(Camera* camera);

    void update(const FrameInfo& frame);

    void render();

    Graphics* getGraphics() const;
private:
    Graphics* graphics_;

    FrameInfo frame_;

    Camera* cullCamera_;

    glm::vec2 viewSize_;
};
