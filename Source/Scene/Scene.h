//
// Created by liuqian8 on 2019/7/10.
//
#pragma once
#include "Node.h"

class Scene: public Node
{
    ENGINE_OBJECT(Scene,Node);
public:
    Scene(Context* context);

    virtual ~Scene();

    virtual bool load(std::string source, bool setInstanceDefault = false) override;


};
