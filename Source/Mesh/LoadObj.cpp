#include "LoadObj.h"
#include "PString.h"

#include <iostream>
#include <fstream>
#include <string>
#include <Common.h>
#include <glm/vec3.hpp>


LoadObj::LoadObj()
{

}

LoadObj::~LoadObj()
{

}

bool LoadObj::ParseObj(const std::string fileName)
{
    if (fileName.substr(fileName.size() - 4, 4) != ".obj")
        return false;

    Vertex_.clear();
    Normal_.clear();
    TexCoord_.clear();

    std::ifstream file(fileName);
    std::string curline;

    while (std::getline(file, curline))
    {
        if(PetrelEngine::firstToken(curline) == "v")
        {
            LOGI("顶点坐标：");
            std::vector<std::string> spos;
            PetrelEngine::split(PetrelEngine::tail(curline).c_str(),spos," ");
            glm::vec3 position;
            position.x = std::stof(spos[0]);
            position.y = std::stof(spos[1]);
            position.z = std::stof(spos[2]);
            LOGI("顶点坐标(float): %f ,%f ,%f",position.x,position.y,position.z);
            Vertex_.push_back(position);
        }
        if(PetrelEngine::firstToken(curline) == "vt")
        {
            LOGI("纹理坐标：");
            std::vector<std::string> stex;
            PetrelEngine::split(PetrelEngine::tail(curline).c_str(),stex," ");
            glm::vec2 texCoord;
            texCoord.x = std::stof(stex[0]);
            texCoord.y = std::stof(stex[1]);
            LOGI("纹理坐标(float): %f ,%f",texCoord.x,texCoord.y);
            TexCoord_.push_back(texCoord);
        }
        if(PetrelEngine::firstToken(curline) == "vn")
        {
            LOGI("法线坐标：");
            std::vector<std::string> snor;
            PetrelEngine::split(PetrelEngine::tail(curline).c_str(),snor," ");
            glm::vec3 Normal;
            Normal.x = std::stof(snor[0]);
            Normal.y = std::stof(snor[1]);
            Normal.z = std::stof(snor[2]);
            LOGI("法线坐标(float): %f , %f, %f",Normal.x,Normal.y,Normal.z);
            Normal_.push_back(Normal);
        }
        if(PetrelEngine::firstToken(curline) == "f")
        {
            LOGI("索引数据：");
            std::vector<std::string> sface,svert;
            PetrelEngine::split(PetrelEngine::tail(curline),sface," ");
            for(int i = 0; i < sface.size(); i ++)
            {
                int vtype;
                PetrelEngine::split(sface[i],svert,"/");
//                LOGI("索引数据split：%s, %s, %s",svert[0].c_str(),svert[1].c_str(),svert[2].c_str());
                if(svert.size() == 1)
                {
                    vtype = 1;// v
                }
                if(svert.size() == 2)
                {
                    vtype = 2;//  v/vt
                }
                if(svert.size() == 3)
                {
                    if(svert[1] != "")
                        vtype = 4;//  v/vt/vn
                    else
                        vtype = 3;//  v//vn
                }
                switch (vtype)
                {
                    case 1:// v
                    {
                        break;
                    }
                    case 2:{
                        break;
                    }
                    case 3:{
                        break;
                    }
                    case 4:{

                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }
        }
        LOGI("curline:%s",curline.c_str());
    }

    return true;
}