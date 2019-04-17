//
// Created by liuqian8 on 2019/4/17.
//
#include "PBRSample.h"
#include "File.h"
PBRSample::PBRSample():
    Context_(NULL)
{

}

PBRSample::~PBRSample()
{

}

void PBRSample::CreateScence(Context *context, int width, int height)
{
    Context_ = context;
    LOGI("PBRSample Create Scence!");

    File* file = new File(Context_);

    std::string testData = file->getStringFromFileAssets("test.txt");

    LOGI("测试数据：%s",testData.c_str());
}

void PBRSample::RenderOneFrame(Context *context)
{
    Context_ = context;
}
