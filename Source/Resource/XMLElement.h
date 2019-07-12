//
// Created by liuqian8 on 2019/7/12.
//
#pragma once
#include "pugixml.hpp"

class XMLFile;
struct xml_node_struct;
class xpath_node;
class xpath_node_set;
class xpath_query;
class xpath_variable_set;

class XMLElement
{
public:
    XMLElement();

    XMLElement(XMLFile* file,pugi::xml_node_struct* node);
    
};
