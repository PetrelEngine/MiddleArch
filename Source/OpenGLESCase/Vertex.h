//
// Created by liuqian8 on 2019/5/6.
//

#pragma once
#include "vec3.hpp"
#include "vec2.hpp"

typedef struct Vertex
{
    glm::vec3    position;
    glm::vec3    normal;
    glm::vec3    tangent;
    glm::vec3    bitangent;
    glm::vec2    texcoord;
} Vertex;

typedef enum AttributeSlot
{
    kPositionSlot   = 0,
    kNormalSlot,
    kTangentSlot,
    kBitangentSlot,
    kTexCoordSlot,
    kEmptySlot = -1
} AttributeSlot;
