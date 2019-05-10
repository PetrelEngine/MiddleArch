#version 300 es
uniform sampler2D DefaultTexture;
layout(location = 0) out vec4 outData0;
layout(location = 1) out vec4 outData1;
layout(location = 2) out vec4 outData2;
layout(location = 3) out vec4 outData3;
in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vPosition;
//out vec4 fragColor;
void main()
{
    vec4 albedo = texture(DefaultTexture,vTexCoord);
    outData0 = vec4(vPosition.xyz,1.0);
    outData1 = vec4(vNormal.xyz,1.0);
    outData2 = vec4(albedo.xyz,1.0);
    outData3 = vec4(vTexCoord.xy,0.0,1.0);
//    fragColor = albedo;
}