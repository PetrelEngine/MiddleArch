//
// Created by liuqian8 on 2019/7/12.
//
#pragma once
#include "Object.h"

class Camera;
class Scene;
class RenderPath;
class View;
class Viewport: public Object
{
    ENGINE_OBJECT(Viewport,Object);
public:
    Viewport(Context* context);

    Viewport(Context* context,Scene* scene,Camera* camera,RenderPath* renderPath = nullptr);

    virtual ~Viewport();

    void setCamera(Camera* camera);

    void setCullCamera(Camera* camera);

    void setScene(Scene* scene);

    void setRenderPath(RenderPath* renderPath);

    Scene* getScene() const;

    Camera* getCamera() const ;

    View* getView() const;

    RenderPath* getRenderPath() const;

    Camera* getCullCamera() const;

    void allocateView();

protected:
    Camera* camera_;

    Camera* cullCamera_;

    Scene* scene_;

    RenderPath* renderPath_;

    View* view_;
};
