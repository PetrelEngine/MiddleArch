//
// Created by liuqian8 on 2019/6/14.
//
#include "Texture.h"
#include "Graphics.h"

GLenum gl3WrapModes[]=
{
    GL_REPEAT,
    GL_MIRRORED_REPEAT,
    GL_CLAMP_TO_EDGE,
    GL_CLAMP_TO_BORDER_EXT
};

Texture::Texture(Context* context):
    Resource(context),
    GPUObject(getSubsystem<Graphics>()),
    levels_(0),
    parametersDirty_(true),
    format_(0),
    sRGB_(false),
    usage_(TEXTURE_STATIC),
    width_(0),
    height_(0),
    depth_(0),
    filterMode_(FILTER_DEFAULT),
    levelsDirty_(false),
    shadowCompare_(false),
    anisotropy_(0)
{
    for(int i = 0; i < MAX_COORDS;i ++)
        addressMode_[i] = ADDRESS_WRAP;
}

Texture::~Texture()
{

}

void Texture::setNumLevels(unsigned levels)
{
    levels_ = levels;
}

void Texture::setFilterMode(TextureFilterMode mode)
{
    filterMode_ = mode;
    parametersDirty_ = true;
}

void Texture::setAddressMode(TextureCoordinate coord, TextureAddressMode mode)
{
    addressMode_[coord] = mode;
    parametersDirty_ = true;
}

void Texture::updateParameters()
{
    if(!object_.name_ || !graphics_)
        return;
    //纹理展开方式的设置
    glTexParameteri(target_,GL_TEXTURE_WRAP_S,gl3WrapModes[COORD_U]);
    glTexParameteri(target_,GL_TEXTURE_WRAP_T,gl3WrapModes[COORD_U]);

    //暂时不开启对于w的展开方式设置
//    glTexParameteri(target_, GL_TEXTURE_WRAP_R, GetWrapMode(addressMode_[COORD_W]));
    //过滤器的设置
    TextureFilterMode filterMode = filterMode_;
    if(filterMode == FILTER_DEFAULT)
        filterMode = graphics_->getDefaultTextureFilterMode();
    switch (filterMode)
    {
        case FILTER_NEAREST:
            if(levels_ < 2)
                glTexParameteri(target_,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
            else
                glTexParameteri(target_,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);
            glTexParameteri(target_,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        case FILTER_BILINEAR:
            if(levels_ < 2)
                glTexParameteri(target_,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
            else
                glTexParameteri(target_,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
            glTexParameteri(target_,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            break;
        case FILTER_ANISOTROPIC:
        case FILTER_TRILINEAR:
            if(levels_ < 2)
                glTexParameteri(target_,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
            else
                glTexParameteri(target_,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(target_,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            break;
        case FILTER_NEAREST_ANISOTROPIC:
            if (levels_ < 2)
                glTexParameteri(target_, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            else
                glTexParameteri(target_, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
            glTexParameteri(target_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            break;
        default:
            break;
    }
    //各向异性采样
    unsigned maxAnisotropy = anisotropy_ ? anisotropy_ : graphics_->getDefaultTextureAnisotropy();
    glTexParameterf(target_, GL_TEXTURE_MAX_ANISOTROPY_EXT,
                    (filterMode == FILTER_ANISOTROPIC || filterMode == FILTER_NEAREST_ANISOTROPIC) ? (float)maxAnisotropy : 1.0f);
//     Shadow compare
    if (shadowCompare_)
    {
        glTexParameteri(target_, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
        glTexParameteri(target_, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
    }else
        glTexParameteri(target_, GL_TEXTURE_COMPARE_MODE, GL_NONE);
    parametersDirty_ = false;
}

bool Texture::getParametersDirty() const
{
    return parametersDirty_;
}

unsigned Texture::getExternalFormat(unsigned format)
{
    return format;
}

unsigned Texture::getDataType(unsigned format)
{
    if (format == GL_DEPTH_COMPONENT || format == GL_DEPTH_COMPONENT24_OES)
        return GL_UNSIGNED_INT;
    else if (format == GL_DEPTH_COMPONENT16)
        return GL_UNSIGNED_SHORT;
    else
        return GL_UNSIGNED_BYTE;
}




