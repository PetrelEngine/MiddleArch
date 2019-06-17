#version 300 es
in vec4 position;
in vec2 texCoords;
in vec3 tangent;
in vec3 bitgent;
uniform mat4 modelMatrix;
uniform mat4 mvpMatrix;
uniform vec3 lightPos;
uniform vec3 eyePos;
out vec2 vTexCoords;
out vec3 vPosition;
out vec3 vEyePos;
out vec3 vLightPos;

void main()
{
    gl_Position = mvpMatrix * vec4(position.xyz,1.0);
    vTexCoords = texCoords.xy;
    vec3 normal = vec3(0.0,0.0,1.0);

    vec3 T = normalize(mat3(modelMatrix) * tangent);
    vec3 B = normalize(mat3(modelMatrix) * bitgent);
    vec3 N = normalize(mat3(modelMatrix) * normal);
    mat3 TBN = transpose(mat3(T,B,N));
    vLightPos = TBN * lightPos;
    vEyePos = TBN * eyePos;
    vPosition = TBN * (modelMatrix * vec4(position.xyz,1.0)).xyz;
}//