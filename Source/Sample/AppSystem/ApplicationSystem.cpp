//
// Created by liuqian8 on 2019/4/17.
//
#include "ApplicationSystem.h"
#include "Graphics.h"
#include "File.h"
#include "ResourceCache.h"
ApplicationSystem::ApplicationSystem():
    CurrApplication_(NULL),
    context_(NULL)
{

}

ApplicationSystem::~ApplicationSystem()
{
    if(CurrApplication_ != NULL)
    {
        delete CurrApplication_;
        CurrApplication_ = NULL;
    }
    if(context_ != NULL)
    {
        delete context_;
        context_ = NULL;
    }
}

void ApplicationSystem::initialEngine(Context* context,int width,int height)
{
    context_ = context;
    //引擎启动，我们注册相关的渲染core对象
    Graphics* graphics = new Graphics(context_);
    context_->registerSubsystem(graphics);
    File* file = new File(context_);
    context_->registerSubsystem(file);
    ResourceCache* resourceCache = new ResourceCache(context_);
    context_->registerSubsystem(resourceCache);
    height_ = height;
    width_ = width;
}

void ApplicationSystem::RegisteredApplication(Application *application)
{
    if(CurrApplication_ != NULL)
    {
        delete CurrApplication_;
        CurrApplication_ = NULL;
    }
    CurrApplication_ = application;
}

Application* ApplicationSystem::GetCurrApplication()
{
    return CurrApplication_;
}

void ApplicationSystem::CreateScence(int width, int height)
{
    if(CurrApplication_ == NULL)
    {
        LOGE("ApplicationSystem.cpp Application is NULL pointer!");
        return ;
    }
    CurrApplication_->BaseCreateScence(context_,width,height);
}

void ApplicationSystem::RenderOneFrame()
{
    if(!CurrApplication_->isInitial())
        CreateScence(width_,height_);
    if(CurrApplication_ == NULL)
    {
        LOGE("ApplicationSystem.cpp Application is NULL pointer!");
        return ;
    }
    CurrApplication_->RenderOneFrame(context_);
}

void ApplicationSystem::Move()
{
    if(CurrApplication_ == NULL)
    {
        LOGE("ApplicationSystem.cpp Application is NULL pointer!");
        return ;
    }
    CurrApplication_->Move();
}

Context* ApplicationSystem::getContext()
{
    return context_;
}

