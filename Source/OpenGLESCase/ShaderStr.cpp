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
                    vec4 wall_albedo = texture(DefaultTexture,vTexCoord);\
                    fragData0 = vec4(vPosition.xyz,1.0);\
                    fragData1 = vec4(vNormal.xyz,1.0);\
                    fragData2 = vec4(wall_albedo.xyz,1.0);\
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
        (      "#version 300 es\n\
                uniform sampler2D gposition;\
                uniform sampler2D gnormal;\
                uniform sampler2D gcolor;\
                uniform sampler2D gdepth;\
                uniform vec2 u_Viewport;\
                uniform vec3 lightPosition;\
                uniform vec3 eyePosition;\
                in vec2 vTexCoord;\
                out vec4 fragColor;\
                void main()\
                {\
                    vec2 tex_coord = gl_FragCoord.xy/u_Viewport;\
                    vec4 position = texture(gposition,tex_coord);\
                    vec4 normal = texture(gnormal,tex_coord);\
                    vec4 color = texture(gcolor,tex_coord);\
                    vec4 depth = texture(gdepth,tex_coord);\
                    vec3 lightAmbient = vec3(0.5,0.5,0.5);\
                    vec3 lightDiffuse = vec3(1.0,1.0,1.0);\
                    vec3 lightSpecular = vec3(1.0,1.0,1.0);\
                    vec3 materialAmbient = vec3(1.0,1.0,1.0);\
                    vec3 materialDiffuse = vec3(1.0,1.0,1.0);\
                    vec3 materialSpecular = vec3(1.0,1.0,1.0);\
                    vec3 eyevec = normalize(eyePosition - position.xyz);\
                    vec3 lightvec = normalize(lightPosition - position.xyz);\
                    vec3 normalvec = normalize(normal.xyz);\
                    vec3 refl = reflect(vec3(0.0,0.0,0.0) - lightvec,normalvec);\
                    vec3 ambient = lightAmbient * materialAmbient;\
                    vec3 diffuse = max(0.0,dot(lightvec,normalvec)) * lightDiffuse * materialDiffuse;\
                    vec3 specular = pow(max(0.0,dot(eyevec,refl)),32.0) * lightSpecular * materialSpecular;\
                    vec4 finalLight = vec4(ambient + diffuse + specular,1.0);\
                    fragColor = finalLight * color;\
                }");