//
// Created by liuqian8 on 2019/4/17.
//

#pragma once

#include "Application.h"

class ApplicationSystem
{
public:
    ApplicationSystem();
    ~ApplicationSystem();

    void RegisteredApplication(Application* application);

    void CreateScence(Context* context,int width,int height);

    void RenderOneFrame(Context* contex);

protected:
    Application* CurrApplication_;
};
