//
// Created by liuqian8 on 2019/5/9.
//

#pragma once

#include <File/File.h>
#include "Context.h"
#include "GLProgram.hpp"

struct Rect
{
    GLuint positionHandle;
    GLuint texcoordsHandle;
    GLuint u_ViewportHandle;
    float* viewport;
    GLuint  gPosition;
    GLuint  gNormal;
    GLuint  gColor;
    GLuint  gDepth;
    GLuint u_lightPosition;
    GLuint u_eyePosition;
    float lightPos[3] = {-8.0f,6.0f,-5.0f};
    float eyePosition[3] = {5.0f,1.0f,-1.0f};
    float positions[8]=
            {
                    1,1,
                    1,-1,
                    -1,-1,
                    -1,1
            };
    float texcoords[8] =
            {
                    1,1,
                    1,0,
                    0,0,
                    0,1
            };
    int index[6] =
            {
                    0,1,2,
                    0,2,3
            };


};

class Rect2D
{
public:
    Rect2D();
    ~Rect2D();

    void CreateRect2D(Context* context,int width,int height);

    void DrawRect2D(Context* context,int* gbuffer);

protected:
    Rect*                       RectHandle;
    Context*                    Context_;
    File*                       File_;
    GLProgram*                GLProgram__;
};
