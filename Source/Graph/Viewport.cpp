//
// Created by liuqian8 on 2019/7/12.
//
#include "Viewport.h"
#include "Camera.h"
#include "View.h"
Viewport::Viewport(Context *context):
    Object(context)
{

}

Viewport::Viewport(Context *context, Scene *scene, Camera *camera, RenderPath *renderPath):
    Object(context),
    scene_(scene),
    camera_(camera),
    renderPath_(renderPath),
    view_(nullptr)
{

}

Viewport::~Viewport()
{
    if(view_ != nullptr)
    {
        delete view_;
        view_ = nullptr;
    }
}

void Viewport::setCamera(Camera *camera)
{
    camera_ = camera;
}

void Viewport::setCullCamera(Camera *camera)
{
    cullCamera_ = camera;
}

void Viewport::setScene(Scene *scene)
{
    scene_ = scene;
}

void Viewport::setRenderPath(RenderPath *renderPath)
{
    renderPath_ = renderPath;
}

Camera* Viewport::getCamera() const
{
    return camera_;
}

Scene* Viewport::getScene() const
{
    return scene_;
}

Camera* Viewport::getCullCamera() const
{
    return cullCamera_;
}

View* Viewport::getView() const
{
    return view_;
}

RenderPath* Viewport::getRenderPath() const
{
   return renderPath_;
}

void Viewport::allocateView()
{
    if(view_ != nullptr)
        return;
    view_ = new View(context_);
}
