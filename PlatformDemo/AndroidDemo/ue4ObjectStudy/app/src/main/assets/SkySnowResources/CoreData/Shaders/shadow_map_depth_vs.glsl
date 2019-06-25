#version 300 es
layout(location = 0)in vec3 positions;
uniform mat4 model;
uniform mat4 vpMatrix;
void main()
{
    gl_Position = vpMatrix * model * vec4(positions,1.0);
}
