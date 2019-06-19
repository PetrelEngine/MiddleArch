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

    void setFilterMode(TextureFilterMode filter);

    void setAddressMode(TextureCoordinate coord, TextureAddressMode address);



protected:
    virtual bool create()
    {
        return true;
    }

    int width_;

    int height_;
    /// Texture usage type.
    TextureUsage usage_;

    unsigned levels_;

    TextureFilterMode filterMode_;

    TextureAddressMode addressMode_[MAX_COORDS];

};
