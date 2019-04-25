//
// Created by liuqian8 on 2019/4/17.
//
#pragma once

#include <string>
#include <vector>
#include "Vertex.h"
#include "Material.h"

struct Mesh
{
    // Default Constructor
    Mesh()
    {

    }
//    // Variable Set Constructor
//    Mesh(std::vector<Vertex>& _Vertices, std::vector<unsigned int>& _vIndices,std::vector<unsigned int>& _vtIndices,std::vector<unsigned int>& _vnIndices)
//    {
//        Vertices = _Vertices;
//    }
    // Mesh Name
    std::string MeshName;
    // Vertex List
    std::vector<Vertex> Vertices;
    // Index List
    std::vector<unsigned int> FinalIndices;

    std::vector<Vector3>      Position;
    std::vector<Vector2>      TextureCoordinate;
    std::vector<Vector3>      Normal;

    std::vector<unsigned int> VertexIndices;
    std::vector<unsigned int> TexCoordIndices;
    std::vector<unsigned int> NormalIndices;

    // Material
    Material MeshMaterial;
};

