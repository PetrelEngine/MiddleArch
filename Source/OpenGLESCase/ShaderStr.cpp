//
// Created by liuqian8 on 2019/5/9.
//
#include "ShaderStr.h"

const std::string ShaderStr::deferrVertex =
        ("      #version 300 es\n \
                in vec4 position;\
                in vec4 texCoord;\
                in vec4 normal;\
                uniform mat4 uMVPMatix;\
                uniform mat4 uModelMatix;\
                out vec2 vTexCoord;\
                out vec3 vNormal;\
                out vec3 vPosition;\
                void main()\
                {\
                    gl_Position = uMVPMatix * vec4(position.xyz,1.0);\
                    vNormal =(uModelMatix * vec4(normal.xyz,1.0)).xyz;\
                    vPosition = (uModelMatix * vec4(position.xyz,1.0)).xyz;\
                    vTexCoord = texCoord.xy;\
                }");


const std::string ShaderStr::deferrfragment=
        ("      #version 300 es\n \
                precision mediump float; \
                uniform sampler2D DefaultTexture;\
                layout(location = 0) out vec4 fragData0;\
                layout(location = 1) out vec4 fragData1;\
                layout(location = 2) out vec4 fragData2;\
                layout(location = 3) out vec4 fragData3;\
                in vec2 vTexCoord;\
                in vec3 vNormal;\
                in vec3 vPosition;\
                void main()\
                {\
                    vec4 albedo = texture(DefaultTexture,vTexCoord);\
                    fragData0 = vec4(vPosition.xyz,1.0);\
                    fragData1 = vec4(normalize(vNormal),1.0);\
                    fragData2 = vec4(albedo.xyz,1.0);\
                    fragData3 = vec4(vTexCoord.xy,0.0,1.0);\
                }");

const std::string ShaderStr::uiVertex=
        ("      #version 300 es\n\
                in vec4 position;\
                in vec4 texCoord;\
                out vec2 vTexCoord;\
                void main()\
                {\
                    gl_Position = vec4(position.xy,0.0,1.0);\
                    vTexCoord = texCoord.xy;\
                }");
const std::string ShaderStr::uifragment=
        ("      #version 300 es\n\
                uniform sampler2D gposition;\
                uniform sampler2D gnormal;\
                uniform sampler2D gcolor;\
                uniform sampler2D gdepth;\
                uniform vec2 u_Viewport;\
                in vec2 vTexCoord;\
                out vec4 fragColor; \
                void main()\
                {\
                    vec2 tex_coord = gl_FragCoord.xy/u_Viewport;\
                    vec4 position = texture(gposition,tex_coord);\
                    vec4 normal = texture(gnormal,tex_coord);\
                    vec4 color = texture(gcolor,vTexCoord);\
                    vec4 depth = texture(gdepth,tex_coord);\
                    fragColor = vec4(tex_coord.xy,0.0,1.0);\
                }");