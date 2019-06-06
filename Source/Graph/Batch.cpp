//
// Created by liuqian8 on 2019/6/4.
//
#include "Batch.h"
#include "Geometry.h"
#include "Graphics.h"
#include "View.h"
void Batch::Prepare(View* view)
{
    if(!vertexShader_ || !pixelShader_)
        return;
    Graphics* graphics = view->GetGraphics();
    graphics->SetShaders(vertexShader_,pixelShader_);
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
