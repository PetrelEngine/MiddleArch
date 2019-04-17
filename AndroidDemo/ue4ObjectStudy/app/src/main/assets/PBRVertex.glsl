attribute vec4 position;
attribute vec4 texCoord;
varying vec2 vTexCoord;
uniform mat4 uMVPMatix;
void main()
{
    gl_Position = uMVPMatix * position;
    vTexCoord = texCoord.xy;
}