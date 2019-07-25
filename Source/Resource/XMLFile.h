//
// Created by liuqian8 on 2019/7/12.
//
#pragma once

#include "Resource.h"
#include "pugixml.hpp"
class xml_document;
class xml_node;
class xpath_node;
class XMLFile: public Resource
{
    ENGINE_OBJECT(XMLFile,Resource);
public:
    XMLFile(Context* context);

    virtual ~XMLFile();

    virtual bool beginLoad(Deserializer& source) override;

private:
    pugi::xml_document document_;
};