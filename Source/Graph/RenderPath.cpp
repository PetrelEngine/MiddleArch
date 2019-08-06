//
// Created by liuqian8 on 2019/7/26.
//
#include "RenderPath.h"
#include "XMLElement.h"
#include "XMLFile.h"
static const char* commandTypeNames[] =
{
        "none",
        "clear",
        "scenepass",
        "quad",
        "forwardlights",
        "lightvolumes",
        "renderui",
        "sendevent",
        nullptr
};
void RenderTargetInfo::load(const XMLElement &element)
{
    name_ = element.getAttribute("name");
    LOGI("RenderTargetInfo name_:%s",name_.c_str());
    tag_ = element.getAttribute("tag");
}

void RenderPathCommand::load(const XMLElement &element)
{
//    type_ = (RenderCommandType)getStringListIndex(element.getAttributeLower("type").c_str(), commandTypeNames, CMD_NONE);
    tag_ = element.getAttribute("tag");
    LOGI("tag_:%s",tag_.c_str());
}


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
    if (!&rootElem)
    {
        LOGE("RenderPath 中rootElem栈上内存为空。");
        return false;
    }
    LOGI("RenderPath 中rootElem栈上内存不为空。");
//
//    XMLElement rtElem = rootElem.getChild("rendertarget");
//    while (&rtElem)
//    {
//        RenderTargetInfo info;
//        info.load(rtElem);
//        if (!info.name_.Trimmed().Empty())
//            renderTargets_.push_back(info);
//
//        rtElem = rtElem.getNext("rendertarget");
//    }
//
    XMLElement cmdElem = rootElem.getChild("command");
    while (&cmdElem)
    {
        RenderPathCommand cmd;
        cmd.load(cmdElem);
        if (cmd.type_ != CMD_NONE)
            commands_.push_back(cmd);

        cmdElem = cmdElem.getNext("command");
    }
    return true;
}
