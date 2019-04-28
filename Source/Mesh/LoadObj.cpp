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

    LoadedVertices.clear();
    LoadedIndices.clear();

    std::vector<Vector3> Positions;
    Positions.clear();
    std::vector<Vector2> TCoords;
    TCoords.clear();
    std::vector<Vector3> Normals;
    Normals.clear();

    std::vector<int>     PositionsIndex;
    PositionsIndex.clear();
    std::vector<int>     TCoordsIndex;
    TCoordsIndex.clear();
    std::vector<int>     NormalsIndex;
    NormalsIndex.clear();

    std::string curline;
    while (std::getline(file, curline))
    {
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

            std::vector<int> vQuadidx,vtQuadidx,vnQuadidx;
            vQuadidx.clear();
            vtQuadidx.clear();
            vnQuadidx.clear();
            std::vector<int> vidx,vtidx,vnidx;
            if((sface.size() == 5)||(sface.size() == 4 && sface[3] != "\r"))
            {
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
            } else{
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

            //顶点索引
            for(int i = 0;i < vidx.size();i ++)
            {
                int index = vidx[i];
                PositionsIndex.push_back(index);
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
        LoadedVertices[i].TextureCoordinate = textureCoordinate;
    }

    for(int i = 0; i < NormalsIndex.size(); i ++)
    {
        Vector3 normal;
        normal = Normals[NormalsIndex[i] - 1];
        LoadedVertices[i].Normal = normal;
    }

    return true;
}
