//
// Created by liuqian8 on 2019/6/21.
//
#include "Material.h"

Material::Material(Context* context):
    Resource(context)
{
}

Material::~Material()
{

}

bool Material::beginLoad(Deserializer &source)
{


    return true;
}
