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

