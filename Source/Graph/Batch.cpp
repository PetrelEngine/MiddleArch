//
// Created by liuqian8 on 2019/6/4.
//
#include "glm/ext.hpp"
#include "Batch.h"
#include "Geometry.h"
#include "Graphics.h"
#include "View.h"
#include "Camera.h"
#include "Technique.h"
void Batch::Prepare(View* view,Camera* camera,bool setModelTransform, bool allowDepthWrite)
{
    if(!vertexShader_ || !pixelShader_)
        return;
    Graphics* graphics = view->GetGraphics();
    //设置着色器
    graphics->SetShaders(vertexShader_,pixelShader_);
    //设置模型矩阵
    graphics->setShaderParameter(VSP_MODEL,modelmatrix_);
    if(pass_ && material_)
    {
        BlendMode blend = pass_->getBlendMode();
        graphics->setBlendMode(blend,pass_->getAlphaToCoverage()||material_->getAlphaToCoverage());

        graphics->setDepthTest(pass_->getDepthTestMode());
        graphics->setDepthWrite(pass_->getDepthWrite() && allowDepthWrite);
    }
    //设置相机相关的参数
    view->setCameraShaderParameters(camera);
}

void Batch::Draw(View* view,Camera* camera,bool allowDepthWrite)
{
    if(!geometry_->IsEmpty())
    {
        Prepare(view,camera,true,allowDepthWrite);
        geometry_->Draw(view->GetGraphics());
    }
}


void BatchGroup::Draw(View *view,Camera* camera, bool allowDepthWrite) const
{

}
