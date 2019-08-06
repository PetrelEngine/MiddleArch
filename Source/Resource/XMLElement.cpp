//
// Created by liuqian8 on 2019/7/22.
//
#include "XMLElement.h"

XMLElement::XMLElement():
    node_(nullptr),
    xPathResultSet_(nullptr),
    xpathNode_(nullptr),
    xpathResultIndex_(0)
{
}

XMLElement::XMLElement(XMLFile *file, pugi::xml_node_struct *node):
    file_(file),
    node_(node),
    xPathResultSet_(nullptr),
    xpathNode_(nullptr),
    xpathResultIndex_(0)
{
}

XMLElement::XMLElement(XMLFile *file, const XPathResultSet *resultSet,
                       const pugi::xpath_node *xpathNode, unsigned xpathResultIndex):
    file_(file),
    node_(nullptr),
    xPathResultSet_(resultSet),
    xpathNode_(resultSet?xpathNode:(xpathNode? new pugi::xpath_node(*xpathNode): nullptr)),
    xpathResultIndex_(xpathResultIndex)
{
}

XMLElement::XMLElement(const XMLElement &rhs):
    file_(rhs.file_),
    node_(rhs.node_),
    xPathResultSet_(rhs.xPathResultSet_),
    xpathNode_(rhs.xPathResultSet_ ? rhs.xpathNode_ : (rhs.xpathNode_ ? new pugi::xpath_node(*rhs.xpathNode_) : nullptr)),
    xpathResultIndex_(rhs.xpathResultIndex_)
{
}

XMLElement::~XMLElement()
{
    if(!xPathResultSet_ && xpathNode_)
    {
        delete xpathNode_;
        xpathNode_ = nullptr;
    }
}

XMLElement& XMLElement::operator=(const XMLElement &rhs)
{
    file_ = rhs.file_;
    node_ = rhs.node_;
    xPathResultSet_ = rhs.xPathResultSet_;
    xpathNode_ = rhs.xPathResultSet_ ? rhs.xpathNode_ : (rhs.xpathNode_ ? new pugi::xpath_node(*rhs.xpathNode_) : nullptr);
    xpathResultIndex_ = rhs.xpathResultIndex_;
    return *this;
}

XMLElement XMLElement::createChild(const std::string &name)
{
    return createChild(name.c_str());
}

XMLElement XMLElement::createChild(const char *name)
{
    if(!file_ || (!node_ && !xpathNode_))
    {
        return XMLElement();
    }
    const pugi::xml_node& node = xpathNode_ ? xpathNode_->node() : pugi::xml_node(node_);
    pugi::xml_node child = const_cast<pugi::xml_node&>(node).append_child(name);
    return XMLElement(file_, child.internal_object());
}

bool XMLElement::isNull() const
{
    return !notNull();
}

bool XMLElement::notNull() const
{
    return node_ || (xpathNode_ && !xpathNode_->operator !());
}

XMLElement XMLElement::getOrCreateChild(const std::string& name)
{
    XMLElement child = getChild(name);
    if (child.notNull())
        return child;
    else
        return createChild(name);
}

XMLElement XMLElement::getOrCreateChild(const char* name)
{
    XMLElement child = getChild(name);
    if (child.notNull())
        return child;
    else
        return createChild(name);
}

bool XMLElement::appendChild(XMLElement element, bool asCopy)
{
    if (!element.file_ || (!element.node_ && !element.xpathNode_) || !file_ || (!node_ && !xpathNode_))
        return false;

    pugi::xml_node node = xpathNode_ ? xpathNode_->node() : pugi::xml_node(node_);
    const pugi::xml_node& child = element.xpathNode_ ? element.xpathNode_->node() : pugi::xml_node(element.node_);

    if (asCopy)
        node.append_copy(child);
    else
        node.append_move(child);
    return true;
}

bool XMLElement::remove()
{
    return getParent().removeChild(*this);
}

bool XMLElement::removeChild(const XMLElement& element)
{
    if (!element.file_ || (!element.node_ && !element.xpathNode_) || !file_ || (!node_ && !xpathNode_))
        return false;

    const pugi::xml_node& node = xpathNode_ ? xpathNode_->node() : pugi::xml_node(node_);
    const pugi::xml_node& child = element.xpathNode_ ? element.xpathNode_->node() : pugi::xml_node(element.node_);
    return const_cast<pugi::xml_node&>(node).remove_child(child);
}

bool XMLElement::removeChild(const std::string& name)
{
    return removeChild(name.c_str());
}

bool XMLElement::removeChild(const char* name)
{
    if (!file_ || (!node_ && !xpathNode_))
        return false;

    const pugi::xml_node& node = xpathNode_ ? xpathNode_->node() : pugi::xml_node(node_);
    return const_cast<pugi::xml_node&>(node).remove_child(name);
}

bool XMLElement::removeChildren(const std::string& name)
{
    return removeChildren(name.c_str());
}

bool XMLElement::removeChildren(const char* name)
{
    if ((!file_ || !node_) && !xpathNode_)
        return false;

    const pugi::xml_node& node = xpathNode_ ? xpathNode_->node() : pugi::xml_node(node_);
    if (!strlen(name))
    {
        for (;;)
        {
            pugi::xml_node child = node.last_child();
            if (child.empty())
                break;
            const_cast<pugi::xml_node&>(node).remove_child(child);
        }
    }
    else
    {
        for (;;)
        {
            pugi::xml_node child = node.child(name);
            if (child.empty())
                break;
            const_cast<pugi::xml_node&>(node).remove_child(child);
        }
    }

    return true;
}


bool XMLElement::removeAttribute(const std::string& name)
{
    return removeAttribute(name.c_str());
}

bool XMLElement::removeAttribute(const char* name)
{
    if (!file_ || (!node_ && !xpathNode_))
        return false;

    // If xpath_node contains just attribute, remove it regardless of the specified name
    if (xpathNode_ && xpathNode_->attribute())
        return xpathNode_->parent().remove_attribute(
                xpathNode_->attribute());  // In attribute context, xpath_node's parent is the parent node of the attribute itself

    const pugi::xml_node& node = xpathNode_ ? xpathNode_->node() : pugi::xml_node(node_);
    return const_cast<pugi::xml_node&>(node).remove_attribute(node.attribute(name));
}

XMLElement XMLElement::selectSingle(const std::string& query, pugi::xpath_variable_set* variables) const
{
    if (!file_ || (!node_ && !xpathNode_))
        return XMLElement();

    const pugi::xml_node& node = xpathNode_ ? xpathNode_->node() : pugi::xml_node(node_);
    pugi::xpath_node result = node.select_single_node(query.c_str(), variables);
    return XMLElement(file_, nullptr, &result, 0);
}

XMLElement XMLElement::selectSinglePrepared(const XPathQuery& query) const
{
    if (!file_ || (!node_ && !xpathNode_ && !query.getXPathQuery()))
        return XMLElement();

    const pugi::xml_node& node = xpathNode_ ? xpathNode_->node() : pugi::xml_node(node_);
    pugi::xpath_node result = node.select_single_node(*query.getXPathQuery());
    return XMLElement(file_, nullptr, &result, 0);
}

XPathResultSet XMLElement::select(const std::string& query, pugi::xpath_variable_set* variables) const
{
    if (!file_ || (!node_ && !xpathNode_))
        return XPathResultSet();

    const pugi::xml_node& node = xpathNode_ ? xpathNode_->node() : pugi::xml_node(node_);
    pugi::xpath_node_set result = node.select_nodes(query.c_str(), variables);
    return XPathResultSet(file_, &result);
}

XPathResultSet XMLElement::selectPrepared(const XPathQuery& query) const
{
    if (!file_ || (!node_ && !xpathNode_ && query.getXPathQuery()))
        return XPathResultSet();

    const pugi::xml_node& node = xpathNode_ ? xpathNode_->node() : pugi::xml_node(node_);
    pugi::xpath_node_set result = node.select_nodes(*query.getXPathQuery());
    return XPathResultSet(file_, &result);
}

bool XMLElement::setValue(const std::string& value)
{
    return setValue(value.c_str());
}

bool XMLElement::setValue(const char* value)
{
    if (!file_ || (!node_ && !xpathNode_))
        return false;

    const pugi::xml_node& node = xpathNode_ ? xpathNode_->node() : pugi::xml_node(node_);

    // Search for existing value first
    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling())
    {
        if (child.type() == pugi::node_pcdata)
            return const_cast<pugi::xml_node&>(child).set_value(value);
    }

    // If no previous value found, append new
    return const_cast<pugi::xml_node&>(node).append_child(pugi::node_pcdata).set_value(value);
}

XMLElement XMLElement::getParent() const
{
    if (!file_ || (!node_ && !xpathNode_))
        return XMLElement();

    const pugi::xml_node& node = xpathNode_ ? xpathNode_->node() : pugi::xml_node(node_);
    return XMLElement(file_, node.parent().internal_object());
}

bool XMLElement::setAttribute(const std::string& name, const std::string& value)
{
    return setAttribute(name.c_str(), value.c_str());
}

bool XMLElement::setAttribute(const char* name, const char* value)
{
    if (!file_ || (!node_ && !xpathNode_))
        return false;

    // If xpath_node contains just attribute, set its value regardless of the specified name
    if (xpathNode_ && xpathNode_->attribute())
        return xpathNode_->attribute().set_value(value);

    const pugi::xml_node& node = xpathNode_ ? xpathNode_->node() : pugi::xml_node(node_);
    pugi::xml_attribute attr = node.attribute(name);
    if (attr.empty())
        attr = const_cast<pugi::xml_node&>(node).append_attribute(name);
    return attr.set_value(value);
}

bool XMLElement::setAttribute(const std::string& value)
{
    return setAttribute(value.c_str());
}

bool XMLElement::setAttribute(const char* value)
{
    // If xpath_node contains just attribute, set its value
    return xpathNode_ && xpathNode_->attribute() && xpathNode_->attribute().set_value(value);
}

bool XMLElement::setBool(const std::string& name, bool value)
{
    std::ostringstream os;
    os << value;
    return setAttribute(name, std::string(os.str()));
}

bool XMLElement::setBuffer(const std::string& name, const void* data, unsigned size)
{
    std::string dataStr;
//    BufferToString(dataStr, data, size);
    return setAttribute(name, dataStr);
}

bool XMLElement::setBuffer(const std::string& name, const std::vector<unsigned char>& value)
{
    if (!value.size())
        return setAttribute(name, "");
    else
        return setBuffer(name, &value[0], value.size());
}

XMLElement XMLElement::getChild(const std::string& name) const
{
    return getChild(name.c_str());
}

XMLElement XMLElement::getChild(const char* name) const
{
    if (!file_ || (!node_ && !xpathNode_))
        return XMLElement();

    const pugi::xml_node& node = xpathNode_ ? xpathNode_->node() : pugi::xml_node(node_);
    if (!std::string(name).length())
        return XMLElement(file_, node.first_child().internal_object());
    else
        return XMLElement(file_, node.child(name).internal_object());
}

std::string XMLElement::getAttribute(const char* name) const
{
    return getAttributeCString(name);
}

const char* XMLElement::getAttributeCString(const char* name) const
{
    LOGI("getAttributeCString 0：%s",name);
    if (!file_ || (!node_ && !xpathNode_))
        return nullptr;
    LOGI("getAttributeCString 1");
    // If xpath_node contains just attribute, return it regardless of the specified name
    if (xpathNode_ && xpathNode_->attribute())
        return xpathNode_->attribute().value();
    const pugi::xml_node& node = xpathNode_ ? xpathNode_->node() : pugi::xml_node(node_);
    LOGI("getAttributeCString 3");
    return node.attribute(name).value();
}

XMLElement XMLElement::getNext(const string& name) const
{
    return getNext(name.c_str());
}

XMLElement XMLElement::getNext(const char* name) const
{
    if (!file_ || (!node_ && !xpathNode_))
        return XMLElement();

    const pugi::xml_node& node = xpathNode_ ? xpathNode_->node() : pugi::xml_node(node_);
    if (!string(name).length())
        return XMLElement(file_, node.next_sibling().internal_object());
    else
        return XMLElement(file_, node.next_sibling(name).internal_object());
}

//std::string XMLElement::getAttributeLower(const string& name) const
//{
//    return getAttribute(name).ToLower();
//}
//
//std::string XMLElement::getAttributeLower(const char* name) const
//{
//    return string(getAttribute(name)).ToLower();
//}


XPathResultSet::XPathResultSet()
{

}

XPathResultSet::XPathResultSet(XMLFile *file, pugi::xpath_node_set *resultSet)
{

}

XPathQuery::XPathQuery()
{

}

XPathQuery::XPathQuery(const std::string &queryString, const std::string &variableString)
{

}

XPathQuery::~XPathQuery()
{

}
