#version 300 es
in vec4 iPos;
in vec2 iTexCoord;
in vec3 iNormal;
uniform mat4 cMadel;
uniform mat4 cView;
uniform mat4 cViewProj;
out vec2 vTexCoord;
out vec3 vNormal;
void main()
{
    gl_Position = cViewProj * cView * cMadel * vec4(iPos.xyz,1.0);
    vTexCoord = iTexCoord;
    vNormal = iNormal;
}//