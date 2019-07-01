//
// Created by liuqian8 on 2019/6/27.
//
#include "MSphere.h"
#include <math.h>
#include "Common.h"
MSphere::MSphere():
    longitude_(150.0f),
    latitude_(75.0f),
    longiRadio_(1.0f),
    latiRadio_(2.0f),
    sphereRadius_(2.0f)
{

}

MSphere::~MSphere()
{
    delete vertex_;
    delete normals_;
    delete texcoords_;
    delete index_;
}

void MSphere::generateSphere()
{
    int vStep = 0;
    int iStep = 0;
    int tStep = 0;
    int nStep = 0;
    vertex_ = new float[numVertices() * 3];
    normals_ = new float[numVertices() * 3];
    texcoords_ = new float[numVertices() * 2];
    index_ = new int[numIndex() * 6];
    for(int i = 0; i < longitude_;i ++)
    {
        float phi = (SN_PI/2.0f - (float)i /(longitude_ - 1.0f + 0.0f) * SN_PI) * longiRadio_;
        for(int j = 0; j < latitude_; j ++)
        {
            float theta = ((float)j/(latitude_ + 0.0f) * SN_PI - SN_PI/2.0f) * latiRadio_;
            float r = - sphereRadius_ * cosf(phi);
            float x = r * sinf(theta);
            float y = sphereRadius_ * sinf(phi);
            float z = r * cosf(theta);
            vertex_[vStep++] = x;  // X-axis
            vertex_[vStep++] = y;  // Y-axis;
            vertex_[vStep++] = z; // Z-axis
            texcoords_[tStep++] = ((float)j + 0.0f) / (latitude_ + 0.0f);
            texcoords_[tStep++] = ((float)i + 0.0f)/(longitude_ - 1.0f); //y-axis
            float length = sqrtf(x * x + y * y + z * z);
            normals_[nStep++] = x/length ;
            normals_[nStep++] = y/length;
            normals_[nStep++] = z/length;
        }
    }

    for(int i = 0; i < longitude_-1; i++)
    {
        for(int j = 0; j < latitude_; j++)
        {
            //first triangle
            index_[iStep++] = i * ((int)latitude_ + 1) + j; //upper point
            index_[iStep++] = (i + 1)*((int)latitude_ + 1) + j; // lower point
            index_[iStep++] = i * ((int)latitude_ + 1) + j + 1; // upper-right point

            //second triangle
            index_[iStep++] = (i + 1) * ((int)latitude_ + 1) + j;
            index_[iStep++] = (i + 1) * ((int)latitude_ + 1) + j + 1; // lower-right point
            index_[iStep++] = i * ((int)latitude_ + 1) + j + 1;
        }
    }

}
