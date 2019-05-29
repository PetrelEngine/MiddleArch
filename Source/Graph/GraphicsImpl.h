//
// Created by liuqian8 on 2019/5/29.
//
#pragma once

class GraphicsImpl
{
    friend class Graphics;
public:
    GraphicsImpl();
    ~GraphicsImpl();

private:
    bool vertexBuffersDirty_;
};
