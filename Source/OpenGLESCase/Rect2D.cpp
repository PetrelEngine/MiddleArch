//
// Created by liuqian8 on 2019/5/9.
//

#include "Rect2D.h"
#include "ShaderStr.h"

Rect2D::Rect2D()
{

}

Rect2D::~Rect2D()
{
    if(File_)
    {
        delete File_;
        File_ = NULL;
    }

    if(GLProgram__)
    {
        delete GLProgram__;
        GLProgram__ = NULL;
    }

    if(RectHandle)
    {
        delete RectHandle;
        RectHandle = NULL;
    }
}

void Rect2D::CreateRect2D(Context *context,int width,int height)
{
    Context_ = context;
    //显示GBuffer数据的矩形数据。
    RectHandle = new Rect();
//    File_ = new File(Context_);
//    string vertexShaderSource = File_->getStringFromFileAssets("uiVertex.glsl");
//    string fragShaderSource = File_->getStringFromFileAssets("uiFragment.glsl");

    GLProgram__ = new GLProgram();
    GLProgram__->initWithVertexShaderString(ShaderStr::uiVertex,ShaderStr::uifragment);//ShaderStr::uiVertex,ShaderStr::uifragment  vertexShaderSource,fragShaderSource
    GLProgram__->addAttribute("position");
    GLProgram__->addAttribute("texCoord");
    GLProgram__->link();
    RectHandle->viewport = new float[2];
    RectHandle->viewport[0] = (float)width;
    RectHandle->viewport[1] = (float)height;

    RectHandle->positionHandle = GLProgram__->getAttributeIndex("position");
    RectHandle->texcoordsHandle = GLProgram__->getAttributeIndex("texCoord");
    RectHandle->u_ViewportHandle = GLProgram__->getUniformIndex("u_Viewport");
    RectHandle->gPosition = GLProgram__->getUniformIndex("gposition");
    RectHandle->gNormal = GLProgram__->getUniformIndex("gnormal");
    RectHandle->gColor = GLProgram__->getUniformIndex("gcolor");
    RectHandle->gDepth = GLProgram__->getUniformIndex("gdepth");
    RectHandle->u_lightPosition = GLProgram__->getUniformIndex("lightPosition");
    RectHandle->u_eyePosition = GLProgram__->getUniformIndex("u_eyePosition");

}

void Rect2D::DrawRect2D(Context *context,int* gbuffer)
{
//    uiRect show
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
    glCullFace(GL_FRONT);
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_GEQUAL);
    glUseProgram(GLProgram__->getProgramId());


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gbuffer[0]);
    glUniform1i(RectHandle->gPosition,0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gbuffer[1]);
    glUniform1i(RectHandle->gNormal,1);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, gbuffer[2]);
    glUniform1i(RectHandle->gColor,2);

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, gbuffer[3]);
    glUniform1i(RectHandle->gDepth,3);

    glUniform2fv(RectHandle->u_ViewportHandle, 1, RectHandle->viewport);
    glUniform3fv(RectHandle->u_lightPosition,1,RectHandle->lightPos);
    glUniform3fv(RectHandle->u_eyePosition,1,RectHandle->eyePosition);
    glEnableVertexAttribArray(RectHandle->positionHandle);
    glEnableVertexAttribArray(RectHandle->texcoordsHandle);
    glVertexAttribPointer(RectHandle->positionHandle, 2, GL_FLOAT, GL_FALSE, 0, RectHandle->positions);
    glVertexAttribPointer(RectHandle->texcoordsHandle, 2, GL_FLOAT, GL_FALSE, 0, RectHandle->texcoords);
    glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT,RectHandle->index);

    glActiveTexture(GL_TEXTURE0);
    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
    glCullFace(GL_BACK);
}
