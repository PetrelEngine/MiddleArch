uniform sampler2D DefaultTexture;

varying vec2 vTexCoord;
varying vec3 vNormal;
varying vec3 vPosition;

//layout(location = 0) out vec4 outData0;//position
//layout(location = 1) out vec4 outData1;//normal
//layout(location = 2) out vec4 outData2;//color
//layout(location = 3) out vec4 outData3;//texcoords
//out vec4 fragColor;
void main()
{
    vec4 albedo = texture2D(DefaultTexture,vTexCoord);
//    outData0 = vec4(vPosition.xyz,1.0);
//    outData1 = vec4(normalize(vNormal),1.0);
//    outData2 = vec4(albedo.xyz,1.0);
//    outData3 = vec4(vTexCoord.xy,0.0,1.0);
    gl_FragColor = albedo;
}