varying vec2 vTexCoord;
uniform sampler2D DefaultTexture;
void main()
{
    gl_FragColor = texture2D(DefaultTexture,vTexCoord);//vec4(0.8,1.0,0.6,1.0);//
   }