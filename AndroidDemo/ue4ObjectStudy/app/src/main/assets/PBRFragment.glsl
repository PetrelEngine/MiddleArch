varying vec2 vTexCoord;
uniform sampler2D DefaultTexture;
void main()
{
    gl_FragColor = vec4((vTexCoord.x + 1.0)/2.0,(vTexCoord.y + 1.0)/2.0 - 1.0,0.0,1.0);//texture2D(DefaultTexture, vTexCoord);
}