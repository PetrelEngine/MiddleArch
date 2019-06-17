attribute vec4 position;
attribute vec4 texCoord;
attribute vec4 normal;
varying vec2 vTexCoord;
uniform mat4 uMVPMatix;
void main()
{
    gl_Position = uMVPMatix * vec4(position.xyz,1.0);//vec4(texCoord.x * 2.0 -1.0,(1.0 - texCoord.y) * 2.0 -1.0,0.0,1.0);//
    vTexCoord = texCoord.xy;
   }