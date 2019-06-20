//
// Created by liuqian8 on 2019/6/14.
//
#pragma once

#include "Resource.h"
#include "GPUObject.h"
#include "DataStruct.h"
class Texture: public Resource ,public GPUObject
{
    ENGINE_OBJECT(Texture,Resource);
public:
    Texture(Context* context);

    virtual ~Texture();

    void setNumLevels(unsigned levels);

    void setFilterMode(TextureFilterMode mode);

    void setAddressMode(TextureCoordinate coord, TextureAddressMode mode);

    void regenerateLevels();

    void updateParameters();

    bool getParametersDirty() const;

    unsigned getTarget()const {return target_;}

    TextureUsage getUsage()const {return usage_;}

    unsigned getExternalFormat(unsigned format);

    unsigned getDataType(unsigned format);

protected:
    virtual bool create()
    {
        return true;
    }
    //将纹理对象绑定到GL_TEXTURE_2D、GL_TEXTURE_3D、GL_TEXTURE_2D_ARRAY或者GL_TEXTURE_CUBE_MAP等
    unsigned target_;
    //输入的纹理数据格式。比如说：GL_RED等
    unsigned format_;
    //纹理的宽
    int width_;
    //纹理的高
    int height_;
    ///纹理的深度
    int depth_;
    /// 纹理使用的类型.
    TextureUsage usage_;

    unsigned levels_;

    unsigned requestedLevels_;

    bool parametersDirty_;

    TextureFilterMode filterMode_;

    TextureAddressMode addressMode_[MAX_COORDS];

    //是否使用SRGB
    bool sRGB_;

    bool levelsDirty_;

    unsigned anisotropy_;

    bool shadowCompare_;
};
