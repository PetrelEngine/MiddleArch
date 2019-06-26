#version 300 es
layout(location = 0)in vec3 positions;
layout(location = 1)in vec3 normals;
layout(location = 2)in vec2 texcoords;
uniform mat4 model;
uniform mat4 vpMatrix;
out vec2 vTexcoords;
void main()
{
    gl_Position = vpMatrix * model * vec4(positions,1.0);
    vTexcoords = texcoords;
}
