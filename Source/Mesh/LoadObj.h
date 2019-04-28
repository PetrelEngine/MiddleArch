//
// Created by liuqian8 on 2019/4/16.
//
#pragma once

#include <string>
#include "Mesh.h"

class LoadObj
{
public:
    LoadObj();
    ~LoadObj();
    bool LoadFile(std::string Path);
public:
    // Loaded Vertex Objects
    std::vector<Vertex> LoadedVertices;
    // Loaded Index Positions
    std::vector<unsigned int> LoadedIndices;
};