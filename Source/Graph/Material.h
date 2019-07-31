//
// Created by liuqian8 on 2019/6/20.
//
#pragma once
#include "Resource.h"

class Material;
class Texture;
class Texture2D;
class Technique;
class Pass;
//描述如何渲染一个3D几何体
class Material: public Resource
{
    ENGINE_OBJECT(Material,Resource);
public:
    Material(Context* context);
    virtual ~Material();

    virtual bool beginLoad(Deserializer* source) override;

    bool getAlphaToCoverage() const { return alphaToCoverage_; }

private:
    bool alphaToCoverage_;
};
