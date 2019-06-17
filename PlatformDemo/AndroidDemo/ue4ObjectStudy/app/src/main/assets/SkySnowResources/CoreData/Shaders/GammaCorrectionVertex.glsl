#version 300 es
in vec4 positions;
in vec2 texcoords;
in vec3 normals;
uniform mat4 modeMatrix;
uniform mat4 mvpMatrix;
out vec2 vTexcoords;
out vec3 vPositions;
out vec3 vNormals;
void main()
{
    gl_Position = mvpMatrix * vec4(positions.xyz,1.0);
    vTexcoords = texcoords;
    vPositions = (modeMatrix * vec4(positions.xyz,1.0)).xyz;
    vNormals = normalize((mat3(modeMatrix) * normals.xyz));
}//