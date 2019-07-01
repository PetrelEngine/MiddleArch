#version 300 es
layout(location = 0) in vec3 positions;
layout(location = 1) in vec2 texcoords;
layout(location = 2) in vec3 normals;
uniform mat4 model;
uniform mat4 vpMat;
out vec2 vTexcoords;
out vec3 vWNormals;
out vec3 vWPositions;
void main()
{
    vec4 wordPosition = model * vec4(positions,1.0);
    gl_Position = vpMat * vec4(wordPosition.xyz,1.0);
    vTexcoords = texcoords;
    vWNormals = normalize(mat3(model) * normals);
    vWPositions = wordPosition.xyz;
}//