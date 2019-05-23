//
// Created by liuqian8 on 2019/5/23.
//

#pragma once

#include "Context.h"

class Shader
{
public:
    Shader(Context* context);

    ~Shader();

private:
    std::string vsSourceCode_;
};
