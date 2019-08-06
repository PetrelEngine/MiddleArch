//
// Created by liuqian8 on 2019/7/26.
//
#include "XMLFile.h"
#include "XMLElement.h"
#include "Context.h"
XMLFile::XMLFile(Context *context):
        Resource(context),
        document_(new pugi::xml_document())
{
}

XMLFile::~XMLFile()
{

}

void XMLFile::registerObject(Context *context)
{
    context->registerFactory<XMLFile>();
}

bool XMLFile::beginLoad(Deserializer* source)
{
    unsigned int dataSize = bufferData_.length();
    LOGI("XMLFile dataBuffer length:%d",dataSize);
    if (!document_->load_buffer(const_cast<char*>(bufferData_.c_str()),dataSize))
    {
        LOGE("Zero sized XML data");
        document_->reset();
        return false;
    }
    XMLElement rootElem = getRoot();
    string inherit = rootElem.getAttribute("inherit");
    LOGI("inherit:: %s",inherit.c_str());
    if (!inherit.empty())
    {
        LOGE("读取数据。 XMLFile");
    }
    return true;
}

XMLElement XMLFile::getRoot(const string &name)
{
    pugi::xml_node root = document_->first_child();
    if (root.empty())
    {
        LOGI(" root wei kong name:%s",name.c_str());
        return XMLElement();
    }
    if (!(name == "") && name != root.name())
    {
        LOGI("name:%s",name.c_str());
        return XMLElement();
    }else{
        LOGI("name == :%s",name.c_str());
        return XMLElement(this, root.internal_object());
    }
}

