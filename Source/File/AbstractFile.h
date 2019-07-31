//
// Created by liuqian8 on 2019/7/29.
//
#pragma once

#include "Deserializer.h"
#include "Serializer.h"
class AbstractFile: public Deserializer, public Serializer
{
public:

    AbstractFile() :
            Deserializer()
    {

    }
    /// Construct.
    AbstractFile(unsigned int size)
            : Deserializer(size)
    {
    }
    /// Destruct.
    virtual ~AbstractFile() override { }
};
