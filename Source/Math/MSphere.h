//
// Created by liuqian8 on 2019/6/27.
//
#pragma once

class MSphere
{
public:
    MSphere();
    ~MSphere();

    void generateSphere();

    void setParamerLongitude(float longitude,float longiRadio)
    {
        longitude_ = longitude;
        longiRadio_ = longiRadio;
    }

    void setParamerLatitude(float latitude,float latiRadio)
    {
        latitude_ = latitude;
        latiRadio_ = latiRadio;
    }

    void setParamerRadius(float sphereRadius)
    {
        sphereRadius_ = sphereRadius;
    }

    int numVertices() {return ((int)latitude_+1)*(int)longitude_;}

    int numIndex(){return ((int)longitude_-1)*(int)latitude_;}

private:
    float* vertex_;
    float* texcoords_;
    float* normals_;
    int* index_;

    float longitude_;//经度 是竖直的线
    float latitude_;//纬度 是水平的线

    float longiRadio_;//经度的比例
    float latiRadio_;//纬度的比例

    float sphereRadius_;//球体的半径
};
