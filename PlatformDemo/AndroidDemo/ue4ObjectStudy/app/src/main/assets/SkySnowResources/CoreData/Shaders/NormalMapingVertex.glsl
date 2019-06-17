#version 300 es
in vec4 positions;
in vec3 normals;
in vec2 texCoords;
uniform mat4 modelMatrix;
uniform mat4 mvpMatrix;
out vec3 vPositions;
out vec2 vTexcoords;
out vec3 vNormals;
out vec3 mPosition;
void main()
{
    gl_Position = mvpMatrix * vec4(positions.xyz,1.0);
    vPositions = (modelMatrix * vec4(positions.xyz,1.0)).xyz;
    vNormals = mat3(modelMatrix) * normals;
    vTexcoords = texCoords.xy;
    mPosition = positions.xyz;
}//