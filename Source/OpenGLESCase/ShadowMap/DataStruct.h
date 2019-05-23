//
// Created by liuqian8 on 2019/5/23.
//
#pragma once


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
    }
    VertexElement(VertexElementType type,VertexElementSemantic semantic, unsigned offset):
            type_(type),
            semantic_(semantic),
            offset_(offset)
    {

    }

    VertexElementType       type_;
    VertexElementSemantic   semantic_;
    unsigned                offset_;
};