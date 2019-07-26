//
// Created by liuqian8 on 2019/7/26.
//
#include "XMLFile.h"
#include "XMLElement.h"
XMLFile::XMLFile(Context *context):
        Resource(context)
{
}

XMLFile::~XMLFile()
{

}

bool XMLFile::beginLoad(Deserializer &source)
{

    return true;
}

XMLElement XMLFile::getRoot(const string &name)
{
    pugi::xml_node root = document_.first_child();
    if (root.empty())
        return XMLElement();

    if (!(name == "") && name != root.name())
        return XMLElement();
    else
        return XMLElement(this, root.internal_object());
}

