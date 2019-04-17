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
public:
    std::vector<Mesh> getMeshList()
    {
        return LoadedMeshes;
    }
    std::vector<Vector3>& getVertices()
    {
        std::vector<Vector3> position;
        for(int i = 0; i < LoadedVertices.size(); i ++)
        {
            Vertex vertex_ = LoadedVertices[i];
            Vector3 p;
            p.X = vertex_.Position.X;
            p.Y = vertex_.Position.Y;
            p.Z = vertex_.Position.Z;
            position.push_back(p);
        }
        return position;
    }

    std::vector<Vector2>& getTexCoord()
    {
        std::vector<Vector2> texCoord;
        for(int i = 0; i < LoadedVertices.size(); i ++)
        {
            Vertex vertex_ = LoadedVertices[i];
            Vector2 t;
            t.X = vertex_.TextureCoordinate.X;
            t.Y = vertex_.TextureCoordinate.Y;
            texCoord.push_back(t);
        }
        return texCoord;
    }
    std::vector<Vector3>& getNormal()
    {
        std::vector<Vector3> normal;
        for(int i = 0; i < LoadedVertices.size(); i ++)
        {
            Vertex vertex_ = LoadedVertices[i];
            Vector3 n;
            n.X = vertex_.Normal.X;
            n.Y = vertex_.Normal.Y;
            n.Z = vertex_.Normal.Z;
            normal.push_back(n);
        }
        return normal;
    }

    std::vector<unsigned int>& getIndices()
    {
        return LoadedIndices;
    }

    std::vector<Material>& getMaterials()
    {
        return LoadedMaterials;
    }

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
