//
// Created by liuqian8 on 2019/4/16.
//
#include "LoadObj.h"
#include "algorithm.h"
#include <iostream>
#include <fstream>
#include <Common.h>

LoadObj::LoadObj()
{

}

LoadObj::~LoadObj()
{

}

bool LoadObj::LoadFile(std::string Path)
{
    // If the file is not an .obj file return false
    if (Path.substr(Path.size() - 4, 4) != ".obj")
        return false;

    std::ifstream file(Path);

    if (!file.is_open())
        return false;

    LoadedMeshes.clear();
    LoadedVertices.clear();
    LoadedIndices.clear();

    std::vector<Vector3> Positions;
    std::vector<Vector2> TCoords;
    std::vector<Vector3> Normals;

    std::vector<int>     PositionsIndex;
    std::vector<int>     TCoordsIndex;
    std::vector<int>     NormalsIndex;

    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;

    std::vector<std::string> MeshMatNames;

    bool listening = false;
    std::string meshname;

    Mesh tempMesh;


    std::string curline;
    while (std::getline(file, curline))
    {

//        // Generate a Mesh Object or Prepare for an object to be created
//        if (algorithm::firstToken(curline) == "o" || algorithm::firstToken(curline) == "g" || curline[0] == 'g')
//        {
//            if (!listening)
//            {
//                listening = true;
//
//                if (algorithm::firstToken(curline) == "o" || algorithm::firstToken(curline) == "g")
//                {
//                    meshname = algorithm::tail(curline);
//                }
//                else
//                {
//                    meshname = "unnamed";
//                }
//            }else
//            {
//                // Generate the mesh to put into the array
//
//                if (!Indices.empty() && !Vertices.empty())
//                {
//                    // Create Mesh
//                    tempMesh.MeshName = meshname;
//
//                    // Insert Mesh
//                    LoadedMeshes.push_back(tempMesh);
//
//                    // Cleanup
//                    Vertices.clear();
//                    Indices.clear();
//                    meshname.clear();
//
//                    meshname = algorithm::tail(curline);
//                }else
//                {
//                    if (algorithm::firstToken(curline) == "o" || algorithm::firstToken(curline) == "g")
//                    {
//                        meshname = algorithm::tail(curline);
//                    }
//                    else
//                    {
//                        meshname = "unnamed";
//                    }
//                }
//            }
//        }
        // Generate a Vertex Position
        if (algorithm::firstToken(curline) == "v")
        {
            std::vector<std::string> spos;
            Vector3 vpos;
            algorithm::split(algorithm::tail(curline), spos, " ");

            vpos.X = std::stof(spos[0]);
            vpos.Y = std::stof(spos[1]);
            vpos.Z = std::stof(spos[2]);

            Positions.push_back(vpos);
        }
        // Generate a Vertex Texture Coordinate
        if (algorithm::firstToken(curline) == "vt")
        {
            std::vector<std::string> stex;
            Vector2 vtex;
            algorithm::split(algorithm::tail(curline), stex, " ");

            vtex.X = std::stof(stex[0]);
            vtex.Y = 1.0f - std::stof(stex[1]);
            TCoords.push_back(vtex);
        }
        // Generate a Vertex Normal;
        if (algorithm::firstToken(curline) == "vn")
        {
            std::vector<std::string> snor;
            Vector3 vnor;
            algorithm::split(algorithm::tail(curline), snor, " ");

            vnor.X = std::stof(snor[0]);
            vnor.Y = std::stof(snor[1]);
            vnor.Z = std::stof(snor[2]);

            Normals.push_back(vnor);
        }
        // Generate a Face (vertices & indices)
        if (algorithm::firstToken(curline) == "f")
        {
            //新版加载face的代码
            std::vector<Vertex> vNewVerts;
            std::vector<std::string> sface,svert;
            algorithm::split(algorithm::tail(curline), sface, " ");
            int isQuad;
            std::vector<int> vQuadidx,vtQuadidx,vnQuadidx;
            std::vector<int> vidx,vtidx,vnidx;
            if((sface.size() == 5)||(sface.size() == 4 && sface[3] != "\r"))
            {
                isQuad = true;
                for(int i = 0 ; i < 4; i ++)
                {
                    algorithm::split(sface[i], svert, "/");
                    if(svert.size() == 1)
                    {
                        vQuadidx.push_back(std::stoi(svert[0]));
                    }else if(svert.size() == 2)
                    {
                        vQuadidx.push_back(std::stoi(svert[0]));
                        vtQuadidx.push_back(std::stoi(svert[1]));
                    }else if(svert.size() == 3)
                    {
                        if(svert[1] != "")
                        {
                            vQuadidx.push_back(std::stoi(svert[0]));
                            vtQuadidx.push_back(std::stoi(svert[1]));
                            vnQuadidx.push_back(std::stoi(svert[2]));
                        }else{
                            vQuadidx.push_back(std::stoi(svert[0]));
                            vnQuadidx.push_back(std::stoi(svert[2]));
                        }
                    }
                }
            } else{
                isQuad = false;
                for(int i = 0 ; i < 3; i ++)
                {
                    algorithm::split(sface[i], svert, "/");
                    if(svert.size() == 1)
                    {
                        vidx.push_back(std::stoi(svert[0]));
                    }else if(svert.size() == 2)
                    {
                        vidx.push_back(std::stoi(svert[0]));
                        vtidx.push_back(std::stoi(svert[1]));
                    }else if(svert.size() == 3)
                    {
                        if(svert[1] != "")
                        {
                            vidx.push_back(std::stoi(svert[0]));
                            vtidx.push_back(std::stoi(svert[1]));
                            vnidx.push_back(std::stoi(svert[2]));
                        }else{
                            vidx.push_back(std::stoi(svert[0]));
                            vnidx.push_back(std::stoi(svert[2]));
                        }
                    }
                }
            }

            if(isQuad)
            {
                std::vector<int> standIdx;
                standIdx.clear();
                standIdx.push_back(0);standIdx.push_back(1);standIdx.push_back(2);
                standIdx.push_back(0);standIdx.push_back(2);standIdx.push_back(3);

                for(int i = 0; i < 6; i++)
                {
                    int index = standIdx[i];
                    if(vQuadidx.size() != 0)
                        vidx.push_back(vQuadidx[index]);
                    if(vtQuadidx.size() != 0)
                        vtidx.push_back(vtQuadidx[index]);
                    if(vnQuadidx.size() != 0)
                        vnidx.push_back(vnQuadidx[index]);
                }
            }
            //顶点索引
            for(int i = 0;i < vidx.size();i ++)
            {
                PositionsIndex.push_back(vidx[i]);
            }
            //纹理坐标索引
            for(int i = 0;i < vtidx.size();i ++)
            {
                TCoordsIndex.push_back(vtidx[i]);
            }
            //法线坐标索引
            for(int i = 0;i < vnidx.size();i ++)
            {
                NormalsIndex.push_back(vnidx[i]);
            }
        }

//        // Get Mesh Material Name
//        if (algorithm::firstToken(curline) == "usemtl")
//        {
//            MeshMatNames.push_back(algorithm::tail(curline));
//
//            // Create new Mesh, if Material changes within a group
//            if (!Indices.empty() && !Vertices.empty())
//            {
//                // Create Mesh
//                tempMesh = Mesh(Vertices, Indices);
//                tempMesh.MeshName = meshname;
//                int i = 2;
//                while(1) {
//                    tempMesh.MeshName = meshname + "_" + std::to_string(i);
//
//                    for (auto &m : LoadedMeshes)
//                        if (m.MeshName == tempMesh.MeshName)
//                            continue;
//                    break;
//                }
//
//                // Insert Mesh
//                LoadedMeshes.push_back(tempMesh);
//
//                // Cleanup
//                Vertices.clear();
//                Indices.clear();
//            }
//        }
//        // Load Materials
//        if (algorithm::firstToken(curline) == "mtllib")
//        {
//            // Generate LoadedMaterial
//
//            // Generate a path to the material file
//            std::vector<std::string> temp;
//            algorithm::split(Path, temp, "/");
//
//            std::string pathtomat = "";
//
//            if (temp.size() != 1)
//            {
//                for (int i = 0; i < temp.size() - 1; i++)
//                {
//                    pathtomat += temp[i] + "/";
//                }
//            }
//
//
//            pathtomat += algorithm::tail(curline);
//
//            // Load Materials
//            LoadMaterials(pathtomat);
//        }
    }//循环读取obj文件结束


    for(int i = 0; i < PositionsIndex.size(); i ++)
    {
        Vertex vertex;
        Vector3 position;
        position = Positions[PositionsIndex[i] - 1];
        vertex.Position = position;
        LoadedVertices.push_back(vertex);
        LoadedIndices.push_back((unsigned)i);
    }

    for(int i = 0; i < TCoordsIndex.size(); i ++)
    {
        Vector2 textureCoordinate;
        textureCoordinate = TCoords[TCoordsIndex[i] - 1];
//        textureCoordinate.X = textureCoordinate.X;
//        textureCoordinate.Y = 1.0f - textureCoordinate.Y;
        LoadedVertices[i].TextureCoordinate = textureCoordinate;
    }

    for(int i = 0; i < NormalsIndex.size(); i ++)
    {
        Vector3 normal;
        normal = Normals[NormalsIndex[i] - 1];
        LoadedVertices[i].Normal = normal;
    }

    return true;
//    // Deal with last mesh
//
//    if (!Indices.empty() && !Vertices.empty())
//    {
//        // Create Mesh
//        tempMesh = Mesh(Vertices, Indices);
//        tempMesh.MeshName = meshname;
//
//        // Insert Mesh
//        LoadedMeshes.push_back(tempMesh);
//    }
//
//    file.close();
//
//    // Set Materials for each Mesh
//    for (int i = 0; i < MeshMatNames.size(); i++)
//    {
//        std::string matname = MeshMatNames[i];
//
//        // Find corresponding material name in loaded materials
//        // when found copy material variables into mesh material
//        for (int j = 0; j < LoadedMaterials.size(); j++)
//        {
//            if (LoadedMaterials[j].name == matname)
//            {
//                LoadedMeshes[i].MeshMaterial = LoadedMaterials[j];
//                break;
//            }
//        }
//    }
//
//    if (LoadedMeshes.empty() && LoadedVertices.empty() && LoadedIndices.empty())
//    {
//        return false;
//    }
//    else
//    {
//        return true;
//    }
}

bool LoadObj::LoadMaterials(std::string path)
{
    // If the file is not a material file return false
    if (path.substr(path.size() - 4, path.size()) != ".mtl")
        return false;

    std::ifstream file(path);

    // If the file is not found return false
    if (!file.is_open())
        return false;

    Material tempMaterial;

    bool listening = false;

    // Go through each line looking for material variables
    std::string curline;
    while (std::getline(file, curline))
    {
        // new material and material name
        if (algorithm::firstToken(curline) == "newmtl")
        {
            if (!listening)
            {
                listening = true;

                if (curline.size() > 7)
                {
                    tempMaterial.name = algorithm::tail(curline);
                }
                else
                {
                    tempMaterial.name = "none";
                }
            }
            else
            {
                // Generate the material

                // Push Back loaded Material
                LoadedMaterials.push_back(tempMaterial);

                // Clear Loaded Material
                tempMaterial = Material();

                if (curline.size() > 7)
                {
                    tempMaterial.name = algorithm::tail(curline);
                }
                else
                {
                    tempMaterial.name = "none";
                }
            }
        }
        // Ambient Color
        if (algorithm::firstToken(curline) == "Ka")
        {
            std::vector<std::string> temp;
            algorithm::split(algorithm::tail(curline), temp, " ");

            if (temp.size() != 3)
                continue;

            tempMaterial.Ka.X = std::stof(temp[0]);
            tempMaterial.Ka.Y = std::stof(temp[1]);
            tempMaterial.Ka.Z = std::stof(temp[2]);
        }
        // Diffuse Color
        if (algorithm::firstToken(curline) == "Kd")
        {
            std::vector<std::string> temp;
            algorithm::split(algorithm::tail(curline), temp, " ");

            if (temp.size() != 3)
                continue;

            tempMaterial.Kd.X = std::stof(temp[0]);
            tempMaterial.Kd.Y = std::stof(temp[1]);
            tempMaterial.Kd.Z = std::stof(temp[2]);
        }
        // Specular Color
        if (algorithm::firstToken(curline) == "Ks")
        {
            std::vector<std::string> temp;
            algorithm::split(algorithm::tail(curline), temp, " ");

            if (temp.size() != 3)
                continue;

            tempMaterial.Ks.X = std::stof(temp[0]);
            tempMaterial.Ks.Y = std::stof(temp[1]);
            tempMaterial.Ks.Z = std::stof(temp[2]);
        }
        // Specular Exponent
        if (algorithm::firstToken(curline) == "Ns")
        {
            tempMaterial.Ns = std::stof(algorithm::tail(curline));
        }
        // Optical Density
        if (algorithm::firstToken(curline) == "Ni")
        {
            tempMaterial.Ni = std::stof(algorithm::tail(curline));
        }
        // Dissolve
        if (algorithm::firstToken(curline) == "d")
        {
            tempMaterial.d = std::stof(algorithm::tail(curline));
        }
        // Illumination
        if (algorithm::firstToken(curline) == "illum")
        {
            tempMaterial.illum = std::stoi(algorithm::tail(curline));
        }
        // Ambient Texture Map
        if (algorithm::firstToken(curline) == "map_Ka")
        {
            tempMaterial.map_Ka = algorithm::tail(curline);
        }
        // Diffuse Texture Map
        if (algorithm::firstToken(curline) == "map_Kd")
        {
            tempMaterial.map_Kd = algorithm::tail(curline);
        }
        // Specular Texture Map
        if (algorithm::firstToken(curline) == "map_Ks")
        {
            tempMaterial.map_Ks = algorithm::tail(curline);
        }
        // Specular Hightlight Map
        if (algorithm::firstToken(curline) == "map_Ns")
        {
            tempMaterial.map_Ns = algorithm::tail(curline);
        }
        // Alpha Texture Map
        if (algorithm::firstToken(curline) == "map_d")
        {
            tempMaterial.map_d = algorithm::tail(curline);
        }
        // Bump Map
        if (algorithm::firstToken(curline) == "map_Bump" || algorithm::firstToken(curline) == "map_bump" || algorithm::firstToken(curline) == "bump")
        {
            tempMaterial.map_bump = algorithm::tail(curline);
        }
    }

    // Deal with last material

    // Push Back loaded Material
    LoadedMaterials.push_back(tempMaterial);

    // Test to see if anything was loaded
    // If not return false
    if (LoadedMaterials.empty())
        return false;
        // If so return true
    else
        return true;
}