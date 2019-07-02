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

    void initialEngine(Context* context,int width,int height);

    Application* GetCurrApplication();

    void CreateScence(int width,int height);

    void RenderOneFrame();

    void Move();

    Context* getContext();

protected:
    Application* CurrApplication_;
    Context*    context_;
    int width_;
    int height_;
};
