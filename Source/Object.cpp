//
// Created by liuqian8 on 2019/4/22.
//
#include "Object.h"
#include "Context.h"

TypeInfo::TypeInfo(const char *typeName, const TypeInfo *baseTypeInfo) :
        type_(typeName),
        typeName_(typeName),
        baseTypeInfo_(baseTypeInfo)
{

}
TypeInfo::~TypeInfo()
{
}

bool TypeInfo::isTypeOf(const TypeInfo* typeInfo) const
{
    const TypeInfo* current = this;
    while (current)
    {
        if (current == typeInfo)
            return true;

        current = current->getBaseTypeInfo();
    }

    return false;
}


Object::Object(Context *context) :
        context_(context)
{

}

Object* Object::getSubsystem(string typeName) const
{
    return context_ ->getSubsystem(typeName);
}

Object::~Object()
{

}
