//
// Created by liuqian8 on 2019/7/10.
//
#pragma once
#include <vector>
#include <string>
#include "vec2.hpp"
#include "DataStruct.h"
class XMLElement;
class XMLFile;

enum RenderCommandSortMode
{
    SORT_FRONTTOBACK = 0,
    SORT_BACKTOFRONT
};
enum RenderTargetSizeMode
{
    SIZE_ABSOLUTE = 0,
    SIZE_VIEWPORTDIVISOR,
    SIZE_VIEWPORTMULTIPLIER
};
enum RenderCommandType
{
    CMD_NONE = 0,
    CMD_CLEAR,
    CMD_SCENEPASS,
    CMD_QUAD,
    CMD_FORWARDLIGHTS,
    CMD_LIGHTVOLUMES,
    CMD_RENDERUI,
    CMD_SENDEVENT
};
struct RenderTargetInfo
{
    RenderTargetInfo() :
            size_(0),
            sizeMode_(SIZE_ABSOLUTE),
            multiSample_(1),
            autoResolve_(true),
            enabled_(true),
            cubemap_(false),
            filtered_(false),
            sRGB_(false),
            persistent_(false)
    {
    }

    void load(const XMLElement& element);

    std::string name_;

    std::string tag_;

    unsigned format_;

    glm::vec2 size_;

    RenderTargetSizeMode sizeMode_;

    int multiSample_;

    bool autoResolve_;

    bool enabled_;

    bool cubemap_;

    bool filtered_;

    bool sRGB_;

    bool persistent_;
};

struct RenderPathCommand
{
    RenderPathCommand() :
            clearFlags_(0),
            blendMode_(BLEND_REPLACE),
            enabled_(true),
            useFogColor_(false),
            markToStencil_(false),
            useLitBase_(true),
            vertexLights_(false)
    {
    }

    void load(const XMLElement& element);
    /// Tag name.
    std::string tag_;
    /// Command type.
    RenderCommandType type_;
    /// Sorting mode.
    RenderCommandSortMode sortMode_;
    /// Scene pass name.
    std::string pass_;
    /// Scene pass index. Filled by View.
    unsigned passIndex_;
    /// Command/pass metadata.
    std::string metadata_;
    /// Vertex shader name.
    std::string vertexShaderName_;
    /// Pixel shader name.
    std::string pixelShaderName_;
    /// Vertex shader defines.
    std::string vertexShaderDefines_;
    /// Pixel shader defines.
    std::string pixelShaderDefines_;
    /// Textures.
    std::string textureNames_[MAX_TEXTURE_UNITS];
    /// %Shader parameters.
//    SN_HashMap<std::string, Variant> shaderParameters_;
//    /// Output rendertarget names and faces.
//    Vector<Pair<String, CubeMapFace> > outputs_;
    /// Depth-stencil output name.
    std::string depthStencilName_;
    /// Clear flags. Affects clear command only.
    unsigned clearFlags_;
    /// Clear color. Affects clear command only.
//    Color clearColor_;
    /// Clear depth. Affects clear command only.
    float clearDepth_;
    /// Clear stencil value. Affects clear command only.
    unsigned clearStencil_;
    /// Blend mode. Affects quad command only.
    BlendMode blendMode_;
    /// Enabled flag.
    bool enabled_;
    /// Use fog color for clearing.
    bool useFogColor_;
    /// Mark to stencil flag.
    bool markToStencil_;
    /// Use lit base pass optimization for forward per-pixel lights.
    bool useLitBase_;
    /// Vertex lights flag.
    bool vertexLights_;
    /// Event name.
    std::string eventName_;
};

class RenderPath
{
public:
    RenderPath();

    virtual ~RenderPath();

    bool load(XMLFile* file);

    bool append(XMLFile* file);

    std::vector<RenderTargetInfo> renderTargets_;

    std::vector<RenderPathCommand> commands_;
};
