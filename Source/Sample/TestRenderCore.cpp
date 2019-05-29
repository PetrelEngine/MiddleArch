//
// Created by liuqian8 on 2019/5/29.
//
#include "TestRenderCore.h"
TestRenderCore::TestRenderCore()
{

}

TestRenderCore::~TestRenderCore()
{
    if(File_)
    {
        delete File_;
        File_ = NULL;
    }
}

void TestRenderCore::testShader(Context *context)
{
    Context_ = context;
    File_ = new File(Context_);
    std::string vertexShaderSource = File_->getStringFromFileAssets("NormalMapingVertex.glsl");
    std::string fragShaderSource = File_->getStringFromFileAssets("NormalMappingFragment.glsl");


}
