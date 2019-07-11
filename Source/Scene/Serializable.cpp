//
// Created by liuqian8 on 2019/7/10.
//
#include "Serializable.h"

Serializable::Serializable(Context *context):
    Object(context)
{
}

Serializable::~Serializable()
{

}

bool Serializable::load(std::string source, bool setInstanceDefault)
{
    return false;
}
