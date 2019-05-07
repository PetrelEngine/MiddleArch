uniform sampler2D DefaultTexture;
varying vec2 vTexCoord;
varying vec3 vNormal;

vec4 encode (vec3 normal)
{
    float p = sqrt(normal.z*8.0+8.0);
    return vec4(normal.xy/p + 0.5,0,0);
}

void main()
{
    vec3 albedo = texture2D(DefaultTexture,vTexCoord).rgb;

    /** GBuffer format
    *  [0] RGB: Albedo
    *  [1] RGB: VS Normal
    *  [2] R: Depth
    */
    gl_FragData[0] = vec4(albedo, 1.0);
    gl_FragData[1] = encode(vNormal);
}