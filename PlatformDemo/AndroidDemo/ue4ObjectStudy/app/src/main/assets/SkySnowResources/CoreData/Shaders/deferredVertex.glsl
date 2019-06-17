#version 300 es
in vec4 position;
in vec4 texCoord;
in vec4 normal;

uniform mat4 uMVPMatix;
uniform mat4 uModelMatix;

out vec2 vTexCoord;
out vec3 vNormal;
out vec3 vPosition;
void main()
{
    gl_Position = uMVPMatix * vec4(position.xyz,1.0);
    vNormal =(uModelMatix * vec4(normal.xyz,1.0)).xyz;
    vPosition = (uModelMatix * vec4(position.xyz,1.0)).xyz;
    vTexCoord = texCoord.xy;
}//