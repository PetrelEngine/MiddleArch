varying vec2 vTexCoord;
uniform sampler2D DefaultTexture;
void main()
{
    gl_FragColor = vec4(1.0,0.0,0.0,1.0);//texture2D(DefaultTexture, vTexCoord);
}