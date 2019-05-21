#version 300 es
in vec3 positions;
in vec2 texCoords;
in vec3 normals;
uniform mat4 modelMatrix;
uniform mat4 mvpMatrix;
out vec2 vTexcoords;
out vec3 vNormals;
out vec3 vPositions;
void main()
{
    vTexcoords = texCoords;
    vNormals = mat3(modelMatrix) * normals;
    vPositions = (modelMatrix * vec4(positions,1.0)).xyz;
    gl_Position = mvpMatrix * vec4(positions,1.0);
}//
