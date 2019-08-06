//
// Created by liuqian8 on 2019/7/31.
//
#include "XMLLoadSample.h"
#include "ResourceCache.h"
#include "RenderPath.h"
XMLLoadSample::XMLLoadSample()
{

}

XMLLoadSample::~XMLLoadSample()
{

}

void XMLLoadSample::CreateScence(Context *context, int width, int height)
{
    xmlFile_ = new XMLFile(context);
    ResourceCache* cache = context->getSubsystem<ResourceCache>();

//    cache->getResource<XMLFile>("RenderPaths/Forward.xml");

    defaultRenderPath_ = new RenderPath();
    defaultRenderPath_->load(cache->getResource<XMLFile>("RenderPaths/Forward.xml"));
}

void XMLLoadSample::RenderOneFrame(Context *context)
{
    glClearColor(1.0,0.5,0.5,1.0);
}

void XMLLoadSample::Move()
{

}