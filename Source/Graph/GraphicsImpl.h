//
// Created by liuqian8 on 2019/5/29.
//
#pragma once

#include "ShaderProgram.h"

class GraphicsImpl
{
    friend class Graphics;
public:
    GraphicsImpl();
    ~GraphicsImpl();

private:
    bool vertexBuffersDirty_;
    ShaderProgram* shaderProgram_;
    SN_Map<pair<ShaderVariation*,ShaderVariation*>,ShaderProgram*> shaderPrograms_;
    SN_Map<pair<char,string>,unsigned> vertexAttributes_;
};
