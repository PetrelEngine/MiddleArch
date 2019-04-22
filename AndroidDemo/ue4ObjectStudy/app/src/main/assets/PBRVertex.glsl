attribute vec4 position;
attribute vec4 texCoord;
attribute vec4 normal;
varying vec2 vTexCoord;
uniform mat4 uMVPMatix;
void main()
{
    gl_Position = vec4(vTexCoord.x * 2.0 -1.0,vTexCoord.x * 2.0 -1.0,0.0,1.0);//uMVPMatix * position;
    vTexCoord = texCoord.xy;
   }