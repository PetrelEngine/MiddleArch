//
// Created by liuqian8 on 2019/4/16.
//
#pragma once

#include <string>

class LoadObj
{
public:
    LoadObj();
    ~LoadObj();

    bool loadFile(std::string path);

    bool loadAssets();
};
