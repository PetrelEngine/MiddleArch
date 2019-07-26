//
// Created by liuqian8 on 2019/7/10.
//
#pragma once
#include "Object.h"
#include "Batch.h"
class Graphics;
class RenderPath;
class Renderer:public Object
{
    ENGINE_OBJECT(Renderer,Object);
public:
    Renderer(Context* context);

    virtual ~Renderer();

    void updata(float timeStep);

    void render();

//    void setBatchShaders(Batch& batch);

    void setCullMode(CullMode mode,Camera* camera);
private:
    void initialize();

    void loadShaders();

    void releaseMaterialShaders();

    void createGeometries();

    void createInstancingBuffer();

    Graphics* graphics_;

    bool initialized_;

    RenderPath* defaultRenderPath_;

    Material* defaultMaterial_;
//    Texture2D* defaultLightRamp_;
};
