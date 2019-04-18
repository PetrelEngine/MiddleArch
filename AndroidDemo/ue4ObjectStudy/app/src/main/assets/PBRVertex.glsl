attribute vec4 position;
attribute vec4 texCoord;
attribute vec4 normal;
varying vec2 vTexCoord;
uniform mat4 uMVPMatix;
void main()
{
    gl_Position = uMVPMatix * position;
    vTexCoord = texCoord.xy;
   }