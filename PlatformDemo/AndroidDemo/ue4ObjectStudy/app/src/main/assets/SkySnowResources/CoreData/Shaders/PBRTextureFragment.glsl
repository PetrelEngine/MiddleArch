#version 300 es
uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform sampler2D metallicMap;
uniform sampler2D roughnessMap;
uniform sampler2D aoMap;
uniform vec3 lightPositions[4];
uniform vec3 lightColors[4];
uniform vec3 eyePos;
in vec2 vTexcoords;
in vec3 vNormals;
in vec3 vPositions;
out vec4 fragColor;
float PI = 3.14159265359;
vec3 getNormalFromMap()
{
    vec3 tangentNormal = texture(normalMap,vTexcoords).xyz * 2.0 - 1.0;
    vec3 Q1 = dFdx(vPositions);
    vec3 Q2 = dFdy(vPositions);
    vec2 st1 = dFdx(vTexcoords);
    vec2 st2 = dFdy(vTexcoords);
    vec3 N = normalize(vNormals);
    vec3 T = normalize(Q1 * st2.t - Q2 * st1.t);
    vec3 B = -normalize(cross(N,T));
    mat3 TBN = mat3(T,B,N);
    return normalize(TBN * tangentNormal * vec3(100.0,100.0,1.0));
}
float DistributionGGX(vec3 N, vec3 H,float roughness)
{
    float a = roughness * roughness;
    float a2 = a* a;
    float NdotH = max(dot(N,H),0.0);
    float Ndoth2 = NdotH * NdotH;

    float nom = a2;
    float denom = (Ndoth2 * (a2 - 1.0) + 1.0);
    denom = PI * denom *denom;
    return nom/denom;
}
float GeometrySchlickGGX(float NdotV,float roughness)
{
    float r = (roughness + 1.0);
    float k = (r * r) /8.0;
    float nom = NdotV;
    float denom = NdotV * (1.0 - k) + k;
    return nom/denom;
}
float GeometrySmith(vec3 N ,vec3 V, vec3 L,float roughness)
{
    float NdotV = max(dot(N,V),0.0);
    float NdotL = max(dot(N,L),0.0);
    float ggx2 = GeometrySchlickGGX(NdotV,roughness);
    float ggx1 = GeometrySchlickGGX(NdotL,roughness);
    return ggx1 * ggx2;
}
vec3 fresnelSchlick(float cosTheta,vec3 F0)
{
    return F0 + (1.0 - F0)*pow(1.0 - cosTheta,5.0);
}
void main()
{
    vec3 albedo     = pow(texture(albedoMap,vTexcoords).rgb,vec3(2.2));
    float metallic  = texture(metallicMap,vTexcoords).r;
    float roughness = texture(roughnessMap,vTexcoords).r;
    float ao        = texture(aoMap,vTexcoords).r;
    vec3 N = getNormalFromMap();
    vec3 V = normalize(eyePos - vPositions);

    vec3 F0 = vec3(0.04);
    F0 = mix(F0,albedo,metallic);

    vec3 Lo = vec3(0.0);
    for(int i = 0; i < 4; i++)
    {
        vec3 L = normalize(lightPositions[i] - vPositions);
        vec3 H = normalize(V + L);
        float dis = length(lightPositions[i] - vPositions);
        float attenuation = 1.0/(dis *dis);
        vec3 radiance = lightColors[i] * attenuation;

        float NDF = DistributionGGX(N,H,roughness);
        float G   = GeometrySmith(N,V,L,roughness);
        vec3  F   = fresnelSchlick(max(dot(H,V),0.0),F0);
        vec3 nominator = NDF * G * F;
        float denominator = 4.0 * max(dot(N,V),0.0) * max(dot(N,L),0.0) + 0.001;
        vec3 specular = nominator/denominator;

        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - metallic;

        float NdotL = max(dot(N,L),0.0);

        Lo +=(kD * albedo/PI +specular)*radiance *NdotL;
    }
    vec3 ambient = vec3(0.03)* albedo * ao;
    vec3 color = ambient + Lo;

    color = color/(color + vec3(1.0));
    color = pow(color,vec3(1.0/2.2));
    fragColor = vec4(color,1.0);
}//