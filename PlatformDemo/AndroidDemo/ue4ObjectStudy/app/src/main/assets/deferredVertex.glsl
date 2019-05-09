attribute vec4 position;
attribute vec4 texCoord;
attribute vec4 normal;

uniform mat4 uMVPMatix;
uniform mat4 uModelMatix;

varying vec2 vTexCoord;
varying vec3 vNormal;
varying vec3 vPosition;
void main()
{
    gl_Position = uMVPMatix * vec4(position.xyz,1.0);
    vNormal =(uModelMatix * vec4(normal.xyz,1.0)).xyz;
    vPosition = (uModelMatix * vec4(position.xyz,1.0)).xyz;
    vTexCoord = texCoord.xy;
}//