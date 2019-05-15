//
// Created by liuqian8 on 2019/4/17.
//
#include "ApplicationSystem.h"


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

void ApplicationSystem::CreateScence(Context *context, int width, int height)
{
    if(CurrApplication_ == NULL)
    {
        LOGE("ApplicationSystem.cpp Application is NULL pointer!");
        return ;
    }
    CurrApplication_->CreateScence(context,width,height);
}

void ApplicationSystem::RenderOneFrame(Context *contex)
{
    if(CurrApplication_ == NULL)
    {
        LOGE("ApplicationSystem.cpp Application is NULL pointer!");
        return ;
    }
    CurrApplication_->RenderOneFrame(contex);
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

