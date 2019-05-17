#version 300 es
uniform sampler2D colorMap;
uniform vec3 lightPos[4];
uniform vec3 lightColor[4];
uniform vec3 eyePos;
uniform bool gamma;
in vec2 vTexcoords;
in vec3 vPositions;
in vec3 vNormals;
out vec4 fragColor;
void main()
{
    fragColor = texture(colorMap,vTexcoords);
}