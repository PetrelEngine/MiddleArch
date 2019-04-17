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
private:

    // Generate vertices from a list of positions,
    //	tcoords, normals and a face line
    void GenVerticesFromRawOBJ(std::vector<Vertex>& oVerts,
                               const std::vector<Vector3>& iPositions,
                               const std::vector<Vector2>& iTCoords,
                               const std::vector<Vector3>& iNormals,
                               std::string icurline);

    // Triangulate a list of vertices into a face by printing
    //	inducies corresponding with triangles within it
    void VertexTriangluation(std::vector<unsigned int>& oIndices,
                             const std::vector<Vertex>& iVerts);

    // Load Materials from .mtl file
    bool LoadMaterials(std::string path);
private:
    // Loaded Mesh Objects
    std::vector<Mesh> LoadedMeshes;
    // Loaded Vertex Objects
    std::vector<Vertex> LoadedVertices;
    // Loaded Index Positions
    std::vector<unsigned int> LoadedIndices;
    // Loaded Material Objects
    std::vector<Material> LoadedMaterials;
};
