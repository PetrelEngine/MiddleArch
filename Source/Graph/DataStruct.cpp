//
// Created by liuqian8 on 2019/5/24.
//
#include "DataStruct.h"

extern const unsigned ELEMENT_TYPESIZE[] =
{
        sizeof(int),
        sizeof(float),
        2 * sizeof(float),
        3 * sizeof(float),
        4 * sizeof(float),
        sizeof(unsigned),
        sizeof(unsigned)
};

extern const string   ELEMENT_INDEX[] =
{
     "iPos",
     "iNormal",
     "iBinNormal",
     "iTangetnt",
     "iTexCoord",
     "iColor",
     "iBlendWeight",
     "iBlendIndices",
     "iObjectIndex"
};

extern const string VSP_MODEL("cMadel");
extern const string VSP_VIEW("cView");
extern const string VSP_VIEWPROJ("cViewProj");
extern const string PSP_DIFFUSEMAP("sDiffuseMap");
extern const string PSP_COLOR("cColor");