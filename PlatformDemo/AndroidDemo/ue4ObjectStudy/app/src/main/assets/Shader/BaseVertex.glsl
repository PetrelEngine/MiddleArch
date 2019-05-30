#version 300 es
in vec4 iPos;
in vec2 iTexCoord;
in vec3 iNormal;
out vec2 vTexCoord;
out vec3 vNormal;
void main()
{
    gl_Position = iPos;
    vTexCoord = iTexCoord;
    vNormal = iNormal;
}
