//
// Created by liuqian8 on 2019/7/26.
//
#include "XMLFile.h"
#include "XMLElement.h"
XMLFile::XMLFile(Context *context):
        Resource(context),
        document_(new pugi::xml_document())
{
}

XMLFile::~XMLFile()
{

}

bool XMLFile::beginLoad(Deserializer* source)
{
    unsigned int dataSize = bufferData_.length();
    LOGE("XMLFile dataBuffer length:%d",dataSize);
    if (!document_->load_buffer(const_cast<char*>(bufferData_.c_str()),dataSize))
    {
        LOGE("Zero sized XML data");
        document_->reset();
        return false;
    }
    XMLElement rootElem = getRoot();
    return true;
}

XMLElement XMLFile::getRoot(const string &name)
{
    pugi::xml_node root = document_->first_child();
    if (root.empty())
        return XMLElement();

    if (!(name == "") && name != root.name())
        return XMLElement();
    else
        return XMLElement(this, root.internal_object());
}

