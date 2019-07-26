//
// Created by liuqian8 on 2019/7/26.
//
#include "RenderPath.h"
#include "XMLElement.h"
#include "XMLFile.h"
RenderPath::RenderPath()
{

}

RenderPath::~RenderPath()
{

}

bool RenderPath::load(XMLFile *file)
{
    renderTargets_.clear();
    commands_.clear();
    return append(file);
}

bool RenderPath::append(XMLFile *file)
{
    if (!file)
        return false;

    XMLElement rootElem = file->getRoot();
    if (!rootElem)
        return false;

    XMLElement rtElem = rootElem.getChild("rendertarget");
    while (rtElem)
    {
        RenderTargetInfo info;
//        info.load(rtElem);
//        if (!info.name_.Trimmed().Empty())
//            renderTargets_.push_back(info);
//
//        rtElem = rtElem.getNext("rendertarget");
    }
//
//    XMLElement cmdElem = rootElem->getChild("command");
//    while (cmdElem)
//    {
//        RenderPathCommand cmd;
//        cmd.load(cmdElem);
//        if (cmd.type_ != CMD_NONE)
//            commands_.push_back(cmd);
//
//        cmdElem = cmdElem.getNext("command");
//    }
    return true;
}
