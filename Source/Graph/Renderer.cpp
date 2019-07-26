//
// Created by liuqian8 on 2019/7/10.
//
#include "Renderer.h"
#include "Camera.h"
#include "Graphics.h"
#include "ResourceCache.h"
#include "Material.h"
#include "RenderPath.h"
#include "XMLFile.h"
Renderer::Renderer(Context* context):
    Object(context),
    initialized_(false)
{
    initialize();
}

Renderer::~Renderer()
{

}

void Renderer::initialize()
{
    Graphics* graphics = getSubsystem<Graphics>();
    ResourceCache* cache = getSubsystem<ResourceCache>();

    if(!graphics || !cache)
        return;

    graphics_ = graphics;

    defaultMaterial_ = new Material(context_);

    defaultRenderPath_ = new RenderPath();

    defaultRenderPath_->load(cache->getResource<XMLFile>("RenderPaths/Forward.xml"));

    createGeometries();

    createInstancingBuffer();

    initialized_ = true;
}

void Renderer::loadShaders()
{

}

void Renderer::updata(float timeStep)
{

}

void Renderer::render()
{

}

void Renderer::releaseMaterialShaders()
{

}

void Renderer::setCullMode(CullMode mode, Camera *camera)
{

}

void Renderer::createGeometries()
{

}

void Renderer::createInstancingBuffer()
{

}

