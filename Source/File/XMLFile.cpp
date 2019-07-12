//
// Created by liuqian8 on 2019/7/12.
//
#include "XMLFile.h"
#include "pugixml.hpp"
XMLFile::XMLFile(Context *context):
    Resource(context)
{

}

XMLFile::~XMLFile()
{

}

bool XMLFile::beginLoad(Deserializer &source)
{
    return false;
}



