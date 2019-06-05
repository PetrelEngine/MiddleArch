//
// Created by liuqian8 on 2019/5/23.
//
#pragma once
#include "Common.h"
#define MAX_VERTEX_STREAMS 4

extern const string   ELEMENT_INDEX[];
enum ShaderType
{
    VS = 0,
    PS,
};

//混合模型
enum BlendMode
{
    BLEND_REPLACE = 0,
    BLEND_ADD,
    BLEDN_MULTIPY,
    BLEND_ALPHA,
    BLEND_ADDALPHA,
    BLEND_PREMULALPHA,
    BLEND_INVDESTALPHA,
    BLEND_SUBTRACT,
    BLEND_SUBTRACTALPHA,
    MAX_BLENDMODES
};

enum CompareMode
{
    CMP_ALWAYS = 0,
    CMP_EQUAL,
    CMP_NOTEQUAL,
    CMP_LESS,
    CMP_LESSEQUAL,
    CMP_GREATER,
    CMP_GREATEREQUAL,
    CMP_COMPAREMODES
};

enum CullMode
{
    CULL_NONE = 0,
    CULL_CCW,//逆时针为正面
    CULL_CW,//顺时针为正面
    MAX_CULLMODES
};

/// Primitive type.
enum PrimitiveType
{
    TRIANGLE_LIST = 0,
    LINE_LIST,
    POINT_LIST,
    TRIANGLE_STRIP,
    LINE_STRIP,
    TRIANGLE_FAN
};

enum VertexElementType
{
    TYPE_INT = 0,
    TYPE_FLOAT,
    TYPE_VECTOR2,
    TYPE_VECTOR3,
    TYPE_VECTOR4,
    TYPE_UBYTE4,
    TYPE_UBYTE4_NORM,
    MAX_VERTEX_ELEMENT_TYPES
};

/// Arbitrary vertex declaration element semantics.
enum VertexElementSemantic
{
    SEM_POSITION = 0,
    SEM_NORMAL,
    SEM_BINORMAL,
    SEM_TANGENT,
    SEM_TEXCOORD,
    SEM_COLOR,
    SEM_BLENDWEIGHTS,
    SEM_BLENDINDICES,
    SEM_OBJECTINDEX,
    MAX_VERTEX_ELEMENT_SEMANTICS
};

struct VertexElement
{
    VertexElement():
            type_(TYPE_VECTOR3),
            semantic_(SEM_POSITION),
            offset_(0)
    {
        index_ = ELEMENT_INDEX[semantic_];
    }
    VertexElement(VertexElementType type,VertexElementSemantic semantic,unsigned offset = 0):
            type_(type),
            semantic_(semantic),
            offset_(offset)
    {
        index_ = ELEMENT_INDEX[semantic];
    }
    std::string             index_;
    VertexElementType       type_;
    VertexElementSemantic   semantic_;
    unsigned                offset_;
};

extern const unsigned ELEMENT_TYPESIZE[];

//初始化着色器的统一属性变量的名字
extern const string VSP_MODEL;//顶点着色器中的模型矩阵
extern const string VSP_VIEW;//顶点着色器中的camera矩阵
extern const string VSP_VIEWPROJ;//顶点着色器中的透视矩阵
extern const string PSP_DIFFUSEMAP;//片元着色器中的默认的贴图
extern const string PSP_COLOR;//片元着色器中的测试颜色数据