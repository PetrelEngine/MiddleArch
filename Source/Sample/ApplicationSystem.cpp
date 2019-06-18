//
// Created by liuqian8 on 2019/4/17.
//
#include "ApplicationSystem.h"
#include "Graphics.h"
#include "File.h"

ApplicationSystem::ApplicationSystem():
    CurrApplication_(NULL)
{

}

ApplicationSystem::~ApplicationSystem()
{
    if(CurrApplication_ != NULL)
    {
        delete CurrApplication_;
        CurrApplication_ = NULL;
    }


}

void ApplicationSystem::initialEngine(Context* context)
{
    context_ = context;
    //引擎启动，我们注册相关的渲染core对象
    Graphics* graphics = new Graphics(context_);
    context_->registerSubsystem(graphics);
    File* file = new File(context_);
    context_->registerSubsystem(file);

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
    CurrApplication_->CreateScence(context_,width,height);
}

void ApplicationSystem::RenderOneFrame()
{
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

