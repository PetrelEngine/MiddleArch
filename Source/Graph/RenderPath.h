//
// Created by liuqian8 on 2019/7/10.
//
#pragma once
#include <vector>

class XMLElement;
class XMLFile;

struct RenderTargetInfo
{

};

struct RenderPathCommand
{

};

class RenderPath
{
public:
    RenderPath();

    virtual ~RenderPath();

    bool load(XMLFile* file);

    bool append(XMLFile* file);

    std::vector<RenderTargetInfo> renderTargets_;

    std::vector<RenderPathCommand> commands_;
};
