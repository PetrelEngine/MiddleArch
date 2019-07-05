#version 300 es
layout(location = 0) in vec3 positions;
layout(location = 1) in vec2 texcoords;

out vec2 vTexcoords;


void main()
{
    gl_Position = vec4(positions.xy,1.0,1.0);
    vTexcoords = texcoords;
}