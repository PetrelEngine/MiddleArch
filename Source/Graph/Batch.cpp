//
// Created by liuqian8 on 2019/6/4.
//
#include <glm/ext.hpp>
#include "Batch.h"
#include "Geometry.h"
#include "Graphics.h"
#include "View.h"
void Batch::Prepare(View* view)
{
    if(!vertexShader_ || !pixelShader_)
        return;
    LOGE("Batch ");
    Graphics* graphics = view->GetGraphics();
    //设置着色器
    graphics->SetShaders(vertexShader_,pixelShader_);
    //设置模型矩阵
    graphics->setShaderParameter(VSP_MODEL,modelmatrix_);
    //设置相机相关的参数
    view->setCameraShaderParameters();
}

void Batch::Draw(View* view)
{
    if(!geometry_->IsEmpty())
    {
        Prepare(view);
        geometry_->Draw(view->GetGraphics());
    }
}


void BatchGroup::Draw(View *view, bool allowDepthWrite) const
{

}
