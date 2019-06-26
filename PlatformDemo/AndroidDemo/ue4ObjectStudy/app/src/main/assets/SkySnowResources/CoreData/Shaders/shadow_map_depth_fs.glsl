#version 300 es
uniform sampler2D diffuseMap;
in vec2 vTexcoords;
out vec4 fragColor;
void main()
{
    fragColor = texture(diffuseMap,vTexcoords);
}
