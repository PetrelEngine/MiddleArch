//
// Created by liuqian8 on 2019/7/12.
//
#pragma once
#include "pugixml.hpp"
#include <string>
#include <glm/fwd.hpp>
#include "vec4.hpp"
#include <sstream>
#include <iostream>
#include <vector>
#include "Common.h"
class XMLFile;
struct xml_node_struct;
class xpath_node;
class xpath_node_set;
class xpath_query;
class xpath_variable_set;
class XMLFile;
class XPathResultSet;
class XPathQuery;
class XMLElement
{
public:
    XMLElement();

    XMLElement(XMLFile* file,pugi::xml_node_struct* node);

    XMLElement(XMLFile* file, const XPathResultSet* resultSet,const pugi::xpath_node* xpathNode,
               unsigned xpathResultIndex);

    XMLElement(const XMLElement& rhs);

    ~XMLElement();

    XMLElement&operator=(const XMLElement& rhs);

    XMLElement createChild(const std::string& name);

    XMLElement createChild(const char* name);

    XMLElement getOrCreateChild(const std::string& name);

    XMLElement getOrCreateChild(const char* name);

    bool appendChild(XMLElement element,bool isCopy = false);

    bool remove();

    bool removeChild(const XMLElement& element);

    bool removeChild(const std::string& name);

    bool removeChild(const char* name);

    bool removeChildren(const std::string& name = "");

    bool removeChildren(const char* name);

    bool removeAttribute(const std::string& name = "");

    bool removeAttribute(const char* name);

    XMLElement selectSingle(const std::string& query,pugi::xpath_variable_set* variables = nullptr) const;

    XMLElement selectSinglePrepared(const XPathQuery& query) const;

    XPathResultSet select(const std::string& query,pugi::xpath_variable_set* variables = nullptr) const;

    XPathResultSet selectPrepared(const XPathQuery& query) const;

    bool setValue(const std::string& value);

    bool setValue(const char* value);
    /// Set an attribute.
    bool setAttribute(const std::string& name, const std::string& value);
    /// Set an attribute.
    bool setAttribute(const char* name, const char* value);
    /// Set an attribute. Only valid if it is an attribute only XPath query result.
    bool setAttribute(const std::string& value);
    /// Set an attribute. Only valid if it is an attribute only XPath query result.
    bool setAttribute(const char* value);
    /// Set a bool attribute.
    bool setBool(const std::string& name, bool value);
    /// Set a buffer attribute.
    bool setBuffer(const std::string& name, const void* data, unsigned size);
    /// Set a buffer attribute.
    bool setBuffer(const std::string& name, const std::vector<unsigned char>& value);
    /// Set a color attribute.
    bool setColor(const std::string& name, const glm::vec4& value);
    /// Set a float attribute.
    bool setFloat(const std::string& name, float value);
    /// Set a double attribute.
    bool setDouble(const std::string& name, double value);
    /// Set an unsigned integer attribute.
    bool setUInt(const std::string& name, unsigned value);
    /// Set an integer attribute.
    bool setInt(const std::string& name, int value);
    /// Set an unsigned long long integer attribute.
    bool setUInt64(const std::string& name, unsigned long long value);
    /// Set a long long integer attribute.
    bool setInt64(const std::string& name, long long value);
    /// Set an IntVector2 attribute.
    bool setIntVector2(const std::string& name, const glm::vec2& value);
    /// Set an IntVector3 attribute.
    bool setIntVector3(const std::string& name, const glm::vec3& value);
    /// Set a Rect attribute.
//    bool SetRect(const std::string& name, const Rect& value);
    /// Set a quaternion attribute.
    bool setQuaternion(const std::string& name, const glm::quat& value);
    /// Set a string attribute.
    bool setString(const std::string& name, const std::string& value);
    /// Set a Vector2 attribute.
    bool setVector2(const std::string& name, const glm::vec2& value);
    /// Set a Vector3 attribute.
    bool setVector3(const std::string& name, const glm::vec3& value);
    /// Set a Vector4 attribute.
    bool setVector4(const std::string& name, const glm::vec4& value);
    /// Set a Matrix3 attribute.
    bool setMatrix3(const std::string& name, const glm::mat3& value);
    /// Set a Matrix3x4 attribute.
    bool setMatrix3x4(const std::string& name, const glm::mat3x4& value);
    /// Set a Matrix4 attribute.
    bool setMatrix4(const std::string& name, const glm::mat4& value);

    /// Return whether does not refer to an element or an XPath node.
    bool isNull() const;
    /// Return whether refers to an element or an XPath node.
    bool notNull() const;

    /// Return child element, or null if missing.
    XMLElement getChild(const std::string& name = "") const;
    /// Return child element, or null if missing.
    XMLElement getChild(const char* name) const;

    XMLElement getParent() const;

    std::string getAttribute(const char* name) const;

    const char* getAttributeCString(const char* name) const;

    /// Return next sibling element.
    XMLElement getNext(const string& name = "") const;
    /// Return next sibling element.
    XMLElement getNext(const char* name) const;

    std::string getAttributeLower(const string& name) const;
    /// Return attribute in lowercase, or empty if missing.
    std::string getAttributeLower(const char* name) const;

private:
    XMLFile* file_;
    pugi::xml_node_struct* node_;
    const XPathResultSet* xPathResultSet_;
    const pugi::xpath_node* xpathNode_;
    mutable unsigned xpathResultIndex_;
};


class XPathResultSet
{
public:
    XPathResultSet();

    XPathResultSet(XMLFile* file, pugi::xpath_node_set* resultSet);
};

class XPathQuery
{
public:
    XPathQuery();

    XPathQuery(const std::string& queryString,const std::string& variableString = "");

    ~XPathQuery();


    std::string getQuery() const { return queryString_; }

    pugi::xpath_query* getXPathQuery() const { return query_; }

private:
    std::string queryString_;
    pugi::xpath_query* query_;
};
