varying vec2 vTexCoord;
uniform sampler2D DefaultTexture;
void main()
{
    gl_FragColor = vec4(vTexCoord.x,vTexCoord.y,0.0,1.0);
  }