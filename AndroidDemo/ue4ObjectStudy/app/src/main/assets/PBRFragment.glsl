varying vec2 vTexCoord;
uniform sampler2D DefaultTexture;
void main()
{
    gl_FragColor = texture2D(DefaultTexture, vTexCoord);
}